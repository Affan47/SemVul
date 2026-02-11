_archive_entry_hardlink_l(struct archive_entry *entry,
    const char **p, size_t *len, struct archive_string_conv *sc)
{
	if ((entry->ae_set & AE_SET_HARDLINK) == 0) {
		*p = NULL;
		*len = 0;
		return (0);
	}
	return (archive_mstring_get_mbs_l(&entry->ae_hardlink, p, len, sc));
}
