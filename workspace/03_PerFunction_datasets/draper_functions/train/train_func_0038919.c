alloc_ifreq(struct ifconf *ifc, int sock)
{
	int ret, lastlen = ifc_last_len, len = ifc_buf_len;
	char err_buf[MAX_ERR_BUF], *buf;

	while (1) {
		buf = malloc(len);
		if (!buf) {
			char *estr = strerror_r(errno, err_buf, MAX_ERR_BUF);
			logerr("malloc: %s", estr);
			return 0;
		}

		ifc->ifc_len = len;
		ifc->ifc_req = (struct ifreq *) buf;

		ret = ioctl(sock, SIOCGIFCONF, ifc);
		if (ret == -1) {
			char *estr = strerror_r(errno, err_buf, MAX_ERR_BUF);
			logerr("ioctl: %s", estr);
			free(buf);
			return 0;
		}

		if (ifc->ifc_len <= lastlen)
			break;

		lastlen = ifc->ifc_len;
		len += MAX_IFC_BUF;
		free(buf);
	}

	if (lastlen != ifc_last_len) {
		ifc_last_len = lastlen;
		ifc_buf_len = len;
	}

	return 1;
}
