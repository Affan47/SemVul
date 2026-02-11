tn_prepare_send(void *buf, int len, void *outbuf, int olen)
{
	char *p = buf;
	int j = 0;
	char *obuf = outbuf;

	for (; len > 0 && j < olen; len--, p++) {
		char c = *p;

		obuf[j++] = c;
		if (j >= olen)
			break;

		if (c == IAC)
			obuf[j++] = c;
		else if (c == '\r')
			obuf[j++] ='\0';
	}

	if (len == 1 && (*p != '\r' && *p != IAC))
		return j;

	if (len > 0)
		return -1;

	return j;
}
