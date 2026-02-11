write_buf(fd, buf, len)
	int		fd;
	char_u	*buf;
	int		len;
{
	int		wlen;

#if defined(NT) && defined(USE_EXFILE) && defined(USE_MATOME)
	int		last = FALSE;
	char_u	*tmp;

	breakcheck();
	if (do_encode)
	{
		if (buf == NULL && len == 0)
			last = TRUE;
		if ((tmp = encode(*encode_buf->b_p_ec, encode_name,
				(encode_buf->b_p_opt & FOPT_MAC_FILE) ? 2 : (encode_buf->b_p_tx ? 1 : 0),
				buf, &len, last)) == NULL)
			return(FAIL);
		if (!last)
			return(OK);
		buf = tmp;
	}
#endif
	while (len)
	{
		wlen = write(fd, (char *)buf, (size_t)len);
		if (wlen <= 0)
#if defined(NT) && defined(USE_EXFILE) && defined(USE_MATOME)
		{
			if (do_encode)
				free(tmp);
			return FAIL;
		}
#else
			return FAIL;
#endif
		len -= wlen;
		buf += wlen;
	}
#if defined(NT) && defined(USE_EXFILE) && defined(USE_MATOME)
	if (do_encode)
		free(tmp);
#endif
	return OK;
}
