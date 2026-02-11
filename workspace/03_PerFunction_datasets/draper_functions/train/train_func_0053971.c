content_info_from_db (CamelFolderSummary *s,
                      CamelMIRecord *mir)
{
	CamelFolderSummaryClass *folder_summary_class;
	gchar *part = mir->cinfo;
	guint32 type = 0;

	folder_summary_class = CAMEL_FOLDER_SUMMARY_CLASS (
		camel_imapx_summary_parent_class);

	if (part) {
		if (*part == ' ')
			part++;
		if (part) {
			type = bdata_extract_digit (&part);
		}
	}
	mir->cinfo = part;
	if (type)
		return folder_summary_class->content_info_from_db (s, mir);
	else
		return camel_folder_summary_content_info_new (s);
}
