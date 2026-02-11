wrap_reco_pass (struct wrap_ccb *wccb, int write_fd,
  unsigned long long length, unsigned write_bsize)
{
	unsigned		cnt;
	int			rc;

	while (length > 0) {
		if (wccb->error)
			break;

		cnt = write_bsize;
		if (cnt > length)
			cnt = length;

		if (wccb->have_length < cnt) {
			wrap_reco_must_have (wccb, cnt);
		}

		rc = write (write_fd, wccb->have, cnt);

		length -= cnt;
		wrap_reco_consume (wccb, cnt);
	}

	return wccb->error;
}
