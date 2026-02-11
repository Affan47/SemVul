open_slot(struct cache_slot *slot)
{
	char *bufz;
	int bufkeylen = -1;

	slot->cache_fd = open(slot->cache_name, O_RDONLY);
	if (slot->cache_fd == -1)
		return errno;

	if (fstat(slot->cache_fd, &slot->cache_st))
		return errno;

	slot->bufsize = xread(slot->cache_fd, slot->buf, sizeof(slot->buf));
	if (slot->bufsize < 0)
		return errno;

	bufz = memchr(slot->buf, 0, slot->bufsize);
	if (bufz)
		bufkeylen = bufz - slot->buf;

	slot->match = bufkeylen == slot->keylen &&
	    !memcmp(slot->key, slot->buf, bufkeylen + 1);

	return 0;
}
