archive_read_support_filter_none(struct archive *a)
{
	archive_check_magic(a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_filter_none");

	return (ARCHIVE_OK);
}
