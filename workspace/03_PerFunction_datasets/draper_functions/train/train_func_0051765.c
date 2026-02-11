summary_header_from_db (CamelFolderSummary *s,
                        CamelFIRecord *fir)
{
	CamelLocalSummary *cls = (CamelLocalSummary *) s;
	gchar *part, *tmp;


	if (!CAMEL_FOLDER_SUMMARY_CLASS (camel_local_summary_parent_class)->summary_header_from_db (s, fir))
		return FALSE;

	part = fir->bdata;
	if (part) {
		EXTRACT_FIRST_DIGIT (cls->version)
	}


	tmp = g_strdup (part);
	g_free (fir->bdata);
	fir->bdata = tmp;

	return TRUE;
}
