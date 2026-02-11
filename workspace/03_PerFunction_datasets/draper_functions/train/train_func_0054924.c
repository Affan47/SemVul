bufferevent_free(struct bufferevent *bufev)
{
	BEV_LOCK(bufev);
	bufferevent_setcb(bufev, NULL, NULL, NULL, NULL);
	_bufferevent_decref_and_unlock(bufev);
}
