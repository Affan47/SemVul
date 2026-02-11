metadata_read_string(FileData *fd, const gchar *key, MetadataFormat format)
{
	GList *string_list = metadata_read_list(fd, key, format);
	if (string_list)
		{
		gchar *str = string_list->data;
		string_list->data = NULL;
		string_list_free(string_list);
		return str;
		}
	return NULL;
}
