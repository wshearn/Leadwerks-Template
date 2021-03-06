#ifndef _EVENTMANAGER_H_
	#define _EVENTMANAGER_H_

#pragma once
#include "Leadwerks.h"
#include "..\Helpers\Delegate.hpp"
#include "..\Helpers\Event.hpp"
#include <list>
#include <map>

/* Define the number of queues the event manager uses internally to process events.*/
#define	NUM_QUEUES 2

typedef Delegate<BaseEventData*>						EventListenerDelegate;																		// Definition fora delegate, specifically used for events.

class EventManager {
	enum eConstants { KINFINITE = 0xffffffff };
	typedef std::list<EventListenerDelegate>			EventListenerList;																			// Definition for a list of event-listener delegates.
	typedef std::map<EventType, EventListenerList>		EventMap;																					// Definition for event-listeners, seperated by event-type.
	typedef std::list<BaseEventData*>					EventQueue;																					// Definition for a queue of event-data.

public:
														EventManager();																				// Event manager constructor.
														~EventManager();																			// Event manager destructor.

	bool												Update(unsigned long nMaxMillis);															// Processes any events within the event-manager's event queue
																																					// for the given amount of time, per frame.
	void												Render();																					// Performs any 3d-rendering for the event manager.
	void												Draw();																						// Performs any 2d-rendering for the event manager.

	bool												AddListener(const EventListenerDelegate& eventDelegate, const EventType& type);				// Adds the given delegate to the event-listener list of the
																																					// - given event-type.
	bool												RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);			// Removes the given delegate from the event-listener list
																																					// - of the given event-type.

	bool												TriggerEvent(BaseEventData& pEvent);														// Immediataly triggers the given event, calling all currently
																																					// - registered listeners to the event.
	bool												QueueEvent(BaseEventData& pEvent);															// Queues the given event to processed during the event-
																																					// - manager's processing queue.
	bool												AbortEvent(const EventType& type, bool bAll = false);										// Aborts the execution of the given event. If bAll is true,
																																					// - all events of the given type are removed from processing.

protected:

private:
	EventMap											m_eventListeners;																			// Contains all event-listeners, seperated by event type.
	EventQueue											m_queues[NUM_QUEUES];																		// Contains all events needing to be processed.
	int													m_nActiveQueue;																				// Indicates which event-processing queue is currently being used.

}; // end class EventManager.

#endif // _EVENTMANAGER_H_