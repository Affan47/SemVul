camel_folder_summary_add_from_parser (CamelFolderSummary *summary,
                                      CamelMimeParser *mp)
{
	CamelMessageInfo *info;

	g_return_val_if_fail (CAMEL_IS_FOLDER_SUMMARY (summary), NULL);
	g_return_val_if_fail (CAMEL_IS_MIME_PARSER (mp), NULL);

	info = camel_folder_summary_info_new_from_parser (summary, mp);

	camel_folder_summary_add (summary, info);

	return info;
}
