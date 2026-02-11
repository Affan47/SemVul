archive_entry_update_symlink_utf8(struct archive_entry *entry, const char *linkname)
{
	if (linkname != NULL)
		entry->ae_set |= AE_SET_SYMLINK;
	else
		entry->ae_set &= ~AE_SET_SYMLINK;
	if (archive_mstring_update_utf8(entry->archive,
	    &entry->ae_symlink, linkname) == 0)
		return (1);
	if (errno == ENOMEM)
		__archive_errx(1, "No memory");
	return (0);
}
