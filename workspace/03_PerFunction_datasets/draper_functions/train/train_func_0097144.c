proxy(int fd, short ev, void *data)
{
	struct proxydesc *d = (struct proxydesc *)data;
	int ret;


	if (ev & EV_READ) {

		ret = read(d->sock, d->dst->iov.iov_base + d->dst->pos,
		    d->dst->iov.iov_len - d->dst->pos);

		switch (ret) {
		case -1:
			if (!(errno == EINTR || errno == EAGAIN)) {
				if (!ISSET(d->state, NET_STATE_EOFPENDING)) {
					SET(d->state, NET_STATE_EOFPENDING);
					break;
				}
				cleanup_cleanup(cleanup);
				errv(0, 1, "(%s)", connstr);
			}
			break;
		case 0:
			if (!ISSET(d->state, NET_STATE_EOFPENDING)) {
				SET(d->state, NET_STATE_EOFPENDING);
				break;
			}
			cleanup_cleanup(cleanup);
			errxv(2, 0, "(%s) Terminated connection", connstr);

		default:
			d->dst->pos += ret;
			break;
		}
	}

	if (ev & EV_WRITE) {
		ret = write(d->sock, d->iov.iov_base, d->pos);

		if (ret == -1) {
			if (errno != EAGAIN) {
				cleanup_cleanup(cleanup);
				errv(0, 1, "(%s)", connstr);
			}
			goto out;
		}

		if (ret == d->pos) {
			d->pos = 0;
		} else {
			memmove(d->iov.iov_base, d->iov.iov_base + ret,
			    d->pos - ret);
			d->pos -= ret;
		}
	}

 out:
	schedule(d);
	if (event_del(d->dst->ev) == -1)
		warnv(0, "event_del()");
	schedule(d->dst);
}
