base64(struct libmail_encode_info *info,
		  const char *buf, size_t n)
{
	if (!buf)
	{
		int rc=0;

		if (info->input_buf_cnt > 0)
			rc=base64_flush(info);

		return rc;
	}

	while (n)
	{
		size_t	i;

		if (info->input_buf_cnt == sizeof(info->input_buffer))
		{
			int rc=base64_flush(info);

			if (rc != 0)
				return rc;
		}

		i=n;
		if (i > sizeof(info->input_buffer) - info->input_buf_cnt)
			i=sizeof(info->input_buffer) - info->input_buf_cnt;

		memcpy(info->input_buffer + info->input_buf_cnt,
		       buf, i);
		info->input_buf_cnt += i;
		buf += i;
		n -= i;
	}
	return 0;
}
