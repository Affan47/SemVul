archive_entry_hardlink(struct archive_entry *entry)
{
	const char *p;
	if ((entry->ae_set & AE_SET_HARDLINK) && archive_mstring_get_mbs(
	    entry->archive, &entry->ae_hardlink, &p) == 0)
		return (p);
	return (NULL);
}
