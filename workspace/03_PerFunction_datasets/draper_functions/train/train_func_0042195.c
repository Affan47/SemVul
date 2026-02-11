detach_socket_net_data(ioa_socket_handle s)
{
	if(s) {
		EVENT_DEL(s->read_event);
		s->read_cb = NULL;
		s->read_ctx = NULL;
		if(s->list_ev) {
			evconnlistener_free(s->list_ev);
			s->list_ev = NULL;
			s->acb = NULL;
			s->acbarg = NULL;
		}
		if(s->conn_bev) {
			bufferevent_disable(s->conn_bev,EV_READ|EV_WRITE);
			bufferevent_free(s->conn_bev);
			s->conn_bev=NULL;
			s->conn_arg=NULL;
			s->conn_cb=NULL;
		}
		if(s->bev) {
			bufferevent_disable(s->bev,EV_READ|EV_WRITE);
			bufferevent_free(s->bev);
			s->bev=NULL;
		}
	}
}
