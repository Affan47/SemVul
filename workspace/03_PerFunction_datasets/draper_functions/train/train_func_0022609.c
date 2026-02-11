removeEventHandler(const Socket& socket, const Poco::AbstractObserver& observer)
{
	NotifierPtr pNotifier;
	{
		FastMutex::ScopedLock lock(_mutex);

		EventHandlerMap::iterator it = _handlers.find(socket);
		if (it != _handlers.end())
		{
			pNotifier = it->second;
			if (pNotifier->countObservers() == 1)
			{
				_handlers.erase(it);
			}
		}
	}
	if (pNotifier)
	{
		pNotifier->removeObserver(this, observer);
	}
}
