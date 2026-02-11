shut_get_string_simple(int upsfd, int index,
			   char *buf, size_t buflen)
{
	unsigned char tbuf[255];
	int ret, si, di;

	ret = shut_control_msg(upsfd, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR,
			(USB_DT_STRING << 8) + index, 0x0, tbuf, buflen, SHUT_TIMEOUT);
	if (ret < 0)
		return ret;

	if (tbuf[1] != USB_DT_STRING)
		return -EIO;

	if (tbuf[0] > ret)
		return -EFBIG;


	for (di = 0, si = 2; si < tbuf[0]; si += 2)
	{
		if (di >= (int)(buflen - 1))
			break;

		if (tbuf[si + 1])
			buf[di++] = '?';
		else
			buf[di++] = tbuf[si];
	}

	buf[di] = 0;
	return di;
}
