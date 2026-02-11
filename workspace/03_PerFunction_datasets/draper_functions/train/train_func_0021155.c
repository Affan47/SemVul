bio_sendto(bio_source_t *bio, const gnet_host_t *to,
	const void *data, size_t len)
{
	size_t available;
	ssize_t r;

	bio_check(bio);
	g_assert(bio->flags & BIO_F_WRITE);


	available = bw_available(bio, len);

	if (available == 0 || available + BW_UDP_OVERSIZE < len) {
		errno = VAL_EAGAIN;
		return -1;
	}

	if (GNET_PROPERTY(bsched_debug) > 7)
		g_debug("BSCHED %s(wio=%d, len=%zu) available=%zu",
			G_STRFUNC, bio->wio->fd(bio->wio), len, available);

	g_assert(bio->wio != NULL);
	g_assert(bio->wio->sendto != NULL);
	r = (*bio->wio->sendto)(bio->wio, to, data, len);


	if ((ssize_t) -1 == r && 0 == errno) {
		g_warning("wio->sendto(fd=%d, len=%zu) returned -1 with errno = 0, "
			"assuming EAGAIN", bio->wio->fd(bio->wio), len);
		errno = VAL_EAGAIN;
	}

	if (r > 0) {
		bsched_bw_update(bsched_get(bio->bws),
			r + BW_UDP_MSG, len + BW_UDP_MSG);
		bio_bw_update(bio, r + BW_UDP_MSG);
	}

	return r;
}
