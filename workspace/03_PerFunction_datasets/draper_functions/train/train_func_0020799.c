del_delete_gfile(MainInfo *min, const GFile *file, gboolean progress, GError **error)
{
	GFileInfo	*fi;
	gboolean	ret = FALSE;

	if(min == NULL || file == NULL)
		return FALSE;

	if((fi = g_file_query_info((GFile *) file, "standard::*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, error)) != NULL)
	{
		switch(g_file_info_get_file_type(fi))
		{
		case G_FILE_TYPE_REGULAR:
		case G_FILE_TYPE_SYMBOLIC_LINK:
		case G_FILE_TYPE_SPECIAL:
		case G_FILE_TYPE_SHORTCUT:
			ret = g_file_delete((GFile *) file, NULL, error);
			break;
		case G_FILE_TYPE_DIRECTORY:
			ret = delete_gfile_dir(min, (GFile *) file, progress, error);
			break;
		default:
			ret = FALSE;
		}
		g_object_unref(fi);
	}
	return ret;
}
