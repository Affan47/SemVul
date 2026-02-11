be_openssl_ctrl(struct bufferevent *bev,
    enum bufferevent_ctrl_op op, union bufferevent_ctrl_data *data)
{
	struct bufferevent_openssl *bev_ssl = upcast(bev);
	switch (op) {
	case BEV_CTRL_SET_FD:
		if (bev_ssl->underlying)
			return -1;
		{
			int flag = 0;
			BIO *bio;
			if (bev_ssl->bev.options & BEV_OPT_CLOSE_ON_FREE)
				flag = 1;
			bio = BIO_new_socket(data->fd, flag);
			SSL_set_bio(bev_ssl->ssl, bio, bio);
			bev_ssl->fd_is_set = 1;
		}
		if (bev_ssl->state == BUFFEREVENT_SSL_OPEN)
			return set_open_callbacks(bev_ssl, data->fd);
		else {
			return set_handshake_callbacks(bev_ssl, data->fd);
		}
	case BEV_CTRL_GET_FD:
		if (bev_ssl->underlying)
			return -1;
		if (!bev_ssl->fd_is_set)
			return -1;
		data->fd = event_get_fd(&bev->ev_read);
		return 0;
	case BEV_CTRL_GET_UNDERLYING:
		if (!bev_ssl->underlying)
			return -1;
		data->ptr = bev_ssl->underlying;
		return 0;
	default:
		return -1;
	}
}
