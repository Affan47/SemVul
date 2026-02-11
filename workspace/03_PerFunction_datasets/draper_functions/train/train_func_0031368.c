copy2mem(struct gfs2_buffer_head *bh, void **buf, unsigned int offset,
	 unsigned int size)
{
	char **p = (char **)buf;

	if (bh)
		memcpy(*p, bh->b_data + offset, size);
	else
		memset(*p, 0, size);

	*p += size;
}
