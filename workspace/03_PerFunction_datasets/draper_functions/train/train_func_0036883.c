do_size_gfile_info(MainInfo *min, const GFile *object, const GFileInfo *fi, guint64 *bytes, FUCount *fc, GError **error)
{
	gboolean	ret = TRUE;

	if(bytes != NULL)
		*bytes += g_file_info_get_size((GFileInfo *) fi);
	if(fc != NULL)
	{
		fc->num_bytes += g_file_info_get_size((GFileInfo *) fi);
		fc->num_blocks += g_file_info_get_attribute_uint64((GFileInfo *) fi, G_FILE_ATTRIBUTE_UNIX_BLOCKS);
	}
	switch(g_file_info_get_file_type((GFileInfo *) fi))
	{
	case G_FILE_TYPE_REGULAR:
		if(fc != NULL)
			fc->num_files++;
		break;
	case G_FILE_TYPE_DIRECTORY:
		if(fc != NULL)
			fc->num_dirs++;
		ret = do_size_gfile_dir(min, object, bytes, fc, error);
		break;
	case G_FILE_TYPE_SYMBOLIC_LINK:
		if(fc != NULL)
			fc->num_links++;
		break;
	case G_FILE_TYPE_SPECIAL:

		break;
	default:
		g_warning("Can't handle irregular file type in do_size_gfile_info()");
	}
	return ret;
}
