copy_gfile(MainInfo *min, DirPane *src, DirPane *dst, GFile *from, GFile *to, GError **err)
{
	GFileInfo	*fi;
	gboolean	ok;

	if(min == NULL || from == NULL || to == NULL)
		return FALSE;

	switch(ovw_overwrite_unary_file(dst, to))
	{
	case OVW_SKIP:
		return TRUE;
	case OVW_CANCEL:
		return FALSE;
	case OVW_PROCEED:
		break;
	case OVW_PROCEED_FILE:
	case OVW_PROCEED_DIR:
		if(!del_delete_gfile(min, to, FALSE, err))
			return FALSE;
	}
	if((fi = g_file_query_info(from, "standard::*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, err)) == NULL)
		return FALSE;
	switch(g_file_info_get_file_type(fi))
	{
	case G_FILE_TYPE_REGULAR:
		pgs_progress_item_begin(min, g_file_info_get_display_name(fi), g_file_info_get_size(fi));
		ok = copy_gfile_regular(min, src, dst, from, to, err);
		pgs_progress_item_end(min);
		break;
	case G_FILE_TYPE_DIRECTORY:
		pgs_progress_item_begin(min, g_file_info_get_display_name(fi), g_file_info_get_size(fi));
		ok = copy_gfile_directory(min, src, dst, from, to, err);
		pgs_progress_item_end(min);
		break;
	case G_FILE_TYPE_SYMBOLIC_LINK:
		pgs_progress_item_begin(min, g_file_info_get_display_name(fi), g_file_info_get_size(fi));
		ok = copy_gfile_symlink(min, src, dst, from, to, err);
		pgs_progress_item_end(min);
		break;
	case G_FILE_TYPE_SPECIAL:
		pgs_progress_item_begin(min, g_file_info_get_display_name(fi), 0);
		ok = copy_gfile_special(min, src, dst, from, to, err);
		pgs_progress_item_end(min);
		break;
	default:
		g_error("Not copying '%s', type is %d which is unsupported", g_file_info_get_name(fi), g_file_info_get_file_type(fi));
		ok = FALSE;
	}
	g_object_unref(fi);

	return ok;
}
