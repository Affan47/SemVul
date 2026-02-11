_e2_filetype_config (gpointer from, E2_ActionRuntime *art)
{

	FileInfo *info = e2_fileview_get_selected_first_local (curr_view, FALSE);
	if (info == NULL)
		return FALSE;

	gchar *ext;

	if (e2_fs_is_dir (info, curr_view))
		ext =  _("<directory>");
	else if (e2_fs_is_executable (info, curr_view))
		ext = _("<executable>");
	else
	{

		ext = strchr (info->filename, '.');
		if (ext == NULL || *(ext+1) == '\0')
			ext = _("<none>");
		else
			ext++;
	}

	gchar *utf = F_FILENAME_FROM_LOCALE (ext);
	e2_filetype_config_show (utf);
	F_FREE (utf);
	return TRUE;
}
