upcast(struct bufferevent *bev)
{
	struct bufferevent_openssl *bev_o;
	if (bev->be_ops != &bufferevent_ops_openssl)
		return NULL;
	bev_o = (void*)( ((char*)bev) -
			 evutil_offsetof(struct bufferevent_openssl, bev.bev));
	EVUTIL_ASSERT(bev_o->bev.bev.be_ops == &bufferevent_ops_openssl);
	return bev_o;
}
