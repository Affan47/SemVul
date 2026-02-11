ndmchan_post_poll (struct ndmchan *chtab[], unsigned n_chtab)
{
	struct ndmchan *	ch;
	unsigned int		i;
	int			rc, len, n_ready;

	n_ready = 0;

	for (i = 0; i < n_chtab; i++) {
		ch = chtab[i];

		if (!ch->ready)
			continue;

		switch (ch->mode) {
		case NDMCHAN_MODE_READ:
			len = ndmchan_n_avail (ch);
			if (len <= 0) continue;

			n_ready++;
			rc = read (ch->fd, &ch->data[ch->end_ix], len);
			if (rc < 0) {
				if (errno != NDMOS_CONST_EWOULDBLOCK) {
					ch->error = ch->eof = 1;
					ch->saved_errno = errno;
					if (!ch->saved_errno)
						ch->saved_errno = -1;
				} else {

				}
			} else if (rc == 0) {
				ch->eof = 1;
				ch->error = 0;
				ch->saved_errno = 0;
			} else {
				ch->end_ix += rc;
			}
			break;

		case NDMCHAN_MODE_WRITE:
			len = ndmchan_n_ready (ch);
			if (len <= 0) continue;

			n_ready++;
			rc = write (ch->fd, &ch->data[ch->beg_ix], len);
			if (rc < 0) {
				if (errno != NDMOS_CONST_EWOULDBLOCK) {
					ch->eof = 1;
					ch->error = 1;
					ch->saved_errno = errno;
					if (!ch->saved_errno)
						ch->saved_errno = -1;
				} else {


				}
			} else if (rc == 0) {

				ch->eof = 1;
				ch->error = 1;
				ch->saved_errno = 0;
			} else {
				ch->beg_ix += rc;
			}
			break;
		}
	}

	return n_ready;
}
