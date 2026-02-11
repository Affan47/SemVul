e_book_backend_summary_check_magic (EBookBackendSummary *summary,
                                    FILE *fp)
{
	gchar buf[PAS_SUMMARY_MAGIC_LEN + 1];
	gint rv;

	memset (buf, 0, sizeof (buf));

	rv = fread (buf, PAS_SUMMARY_MAGIC_LEN, 1, fp);
	if (rv != 1)
		return FALSE;
	if (strcmp (buf, PAS_SUMMARY_MAGIC))
		return FALSE;

	return TRUE;
}
