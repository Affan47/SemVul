connect_eventcb(struct bufferevent *bev, short events, void *ptr)
{
	UNUSED_ARG(bev);

	ioa_socket_handle ret = (ioa_socket_handle) ptr;
	if (ret) {
		connect_cb cb = ret->conn_cb;
		void *arg = ret->conn_arg;
		if (events & BEV_EVENT_CONNECTED) {
			ret->conn_cb = NULL;
			ret->conn_arg = NULL;
			BUFFEREVENT_FREE(ret->conn_bev);
			ret->connected = 1;
			if(cb) {
				cb(1,arg);
			}
		} else if (events & BEV_EVENT_ERROR) {

			ret->conn_cb = NULL;
			ret->conn_arg = NULL;
			BUFFEREVENT_FREE(ret->conn_bev);
			if(cb) {
				cb(0,arg);
			}
		}
	}
}
