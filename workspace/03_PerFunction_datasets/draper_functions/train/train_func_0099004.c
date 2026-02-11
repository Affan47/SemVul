bubbleEvent(Event* evt)
{
	DispatchGuard guard(_inDispatch);
	EventListenerList::iterator it = _listeners.begin();
	while (it != _listeners.end())
	{
		if (it->pListener && !it->useCapture && it->type == evt->type())
		{
			it->pListener->handleEvent(evt);
		}
		if (!it->pListener)
		{
			EventListenerList::iterator del = it++;
			_listeners.erase(del);
		}
		else ++it;
	}
}
