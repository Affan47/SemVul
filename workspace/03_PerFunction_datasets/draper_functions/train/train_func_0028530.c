read_header(struct index_header *dest, const void *buffer)
{
	const struct index_header *source;
	source = (const struct index_header *)(buffer);

	dest->signature = source->signature;
	if (memcmp(&dest->signature, INDEX_HEADER_SIG, 4) != 0)
		return GIT_EOBJCORRUPTED;

	dest->version = ntohl(source->version);
	if (dest->version != INDEX_VERSION_NUMBER)
		return GIT_EOBJCORRUPTED;

	dest->entry_count = ntohl(source->entry_count);
	return 0;
}
