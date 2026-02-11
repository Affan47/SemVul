autowrite(buf)
	BUF		*buf;
{
	if (!p_aw || (!forceit && buf->b_p_ro) || buf->b_filename == NULL)
		return FAIL;
	return buf_write_all(buf);
}
