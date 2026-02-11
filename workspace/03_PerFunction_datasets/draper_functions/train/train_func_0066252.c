doconvtoutf8_rfc822hdr(const char *header,
				  const char *value,
				  struct rfc2045_decodemsgtoutf8_cb *callback)
{
	struct doconvtoutf8_info info;

	info.err_flag=0;
	info.callback=callback;

	if (callback->headerfilter_func &&
	    (*callback->headerfilter_func)(header, value, callback->arg) == 0)
		return 0;

	if ((callback->flags & RFC2045_DECODEMSG_NOHEADERNAME) == 0)
	{
		doconvtoutf8_write(header, strlen(header), &info);
		doconvtoutf8_write(": ", 2, &info);
	}
	rfc822_display_hdrvalue(header, value, "utf-8",
				doconvtoutf8_write,
				doconvtoutf8_error,
				&info);
	doconvtoutf8_write("\n", 1, &info);
	if (callback->headerdone_func && info.err_flag == 0)
	{
		int rc=(*callback->headerdone_func)(header, callback->arg);

		if (rc)
			info.err_flag=rc;
	}

	return info.err_flag;
}
