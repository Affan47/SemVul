add_listener(AggregateListener *l)
{
    for (int i = 0; i < _listeners.size(); i++)
	if (_listeners[i] == l)
	    return;
    _listeners.push_back(l);
}
