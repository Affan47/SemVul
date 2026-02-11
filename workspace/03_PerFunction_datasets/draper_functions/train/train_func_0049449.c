bufferevent_decref_(struct bufferevent *bufev)
{
	BEV_LOCK(bufev);
	return bufferevent_decref_and_unlock_(bufev);
}
