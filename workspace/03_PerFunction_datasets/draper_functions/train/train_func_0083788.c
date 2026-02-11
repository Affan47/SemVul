write_scrollback(unsigned char *buf, int len)
{
	int n;
	if (len > SCROLLSIZE)
	{
		buf = buf + (len - SCROLLSIZE);
		len = SCROLLSIZE;
	}

	n = SCROLLSIZE - scroll_end;
	if (n >= len)
	{
		memcpy(scrollback + scroll_end, buf,
		       len * sizeof(unsigned char));
		scroll_end += len * sizeof(unsigned char);
		scroll_full = 1;
	}
	else
	{
		memcpy(scrollback + scroll_end, buf,
		       n * sizeof(unsigned char));
		scroll_end = len - n;
		memcpy(scrollback, buf,
		       scroll_end * sizeof(unsigned char));
	}
}
