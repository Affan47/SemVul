camel_folder_summary_set_index (CamelFolderSummary *summary,
                                CamelIndex *index)
{
	g_return_if_fail (CAMEL_IS_FOLDER_SUMMARY (summary));

	if (index != NULL)
		g_object_ref (index);

	if (summary->priv->index != NULL)
		g_object_unref (summary->priv->index);

	summary->priv->index = index;
}
