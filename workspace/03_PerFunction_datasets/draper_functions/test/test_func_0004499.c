be_socket_destruct(struct bufferevent *bufev)
{
	struct bufferevent_private *bufev_p =
	    EVUTIL_UPCAST(bufev, struct bufferevent_private, bev);
	evutil_socket_t fd;
	EVUTIL_ASSERT(bufev->be_ops == &bufferevent_ops_socket);

	fd = event_get_fd(&bufev->ev_read);

	event_del(&bufev->ev_read);
	event_del(&bufev->ev_write);

	if (bufev_p->options & BEV_OPT_CLOSE_ON_FREE)
		EVUTIL_CLOSESOCKET(fd);
}
