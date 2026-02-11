libcheck_check (struct checker * c)
{
	struct volume_access_inq inq;
	int ret;

	memset(&inq, 0, sizeof(struct volume_access_inq));
	if (0 != do_inq(c->fd, 0xC9, &inq, sizeof(struct volume_access_inq),
			c->timeout)) {
		ret = PATH_DOWN;
		goto done;
	} else if ((inq.PQ_PDT & 0x20) || (inq.PQ_PDT & 0x7f)) {

		ret = PATH_DOWN;
		goto done;
	}

	ret = ((inq.avtcvp & 0x1) ? PATH_UP : PATH_GHOST);

done:
	switch (ret) {
	case PATH_DOWN:
		MSG(c, MSG_RDAC_DOWN);
		break;
	case PATH_UP:
		MSG(c, MSG_RDAC_UP);
		break;
	case PATH_GHOST:
		MSG(c, MSG_RDAC_GHOST);
		break;
	}

	return ret;
}
