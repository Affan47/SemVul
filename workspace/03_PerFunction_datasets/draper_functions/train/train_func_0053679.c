set_entries_inactive(void)
{
	int i;
	struct io_hdr_stats *shi = st_hdr_cifs;

	for (i = 0; i < cifs_nr; i++, shi++) {
		shi->active = FALSE;
	}
}
