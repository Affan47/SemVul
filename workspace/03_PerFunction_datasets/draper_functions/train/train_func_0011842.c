cache_tree_read(const char *buffer, unsigned long size)
{
	if (buffer[0])
		return NULL;
	return read_one(&buffer, &size);
}
