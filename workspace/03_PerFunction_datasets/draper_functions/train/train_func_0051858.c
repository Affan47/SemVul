http_cb_read(struct bufferevent *bev, void *arg) {
	struct http_connection	*hc=arg;
	Dprintf("%s:%d\n", __FUNCTION__, __LINE__);
	switch(hc->status) {
		case(HC_STATUS_END):
			hc->url_handler(hc, HCB_END, hc->arg);
			break;
		case(HC_STATUS_HEAD):
			if (!http_read_head(hc, bev))
				hc->url_handler(hc, HCB_ERROR, hc->arg);
			break;
		case(HC_STATUS_BODY):
			hc->url_handler(hc, HCB_READ, hc->arg);
			break;
	}
}
