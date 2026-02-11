archive_read_extract(struct archive *_a, struct archive_entry *entry, int flags)
{
	struct extract *extract;

	extract = get_extract((struct archive_read *)_a);
	if (extract == NULL)
		return (ARCHIVE_FATAL);
	archive_write_disk_set_options(extract->ad, flags);
	return (archive_read_extract2(_a, entry, extract->ad));
}
