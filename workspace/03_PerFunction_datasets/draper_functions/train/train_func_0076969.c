_disable()
{
	if (!_source)
		return;
	GPollFD *poll = &(((BusSource *)_source)->poll);
	g_source_remove_poll(_source, poll);
	g_source_destroy(_source);
	_source = NULL;
}
