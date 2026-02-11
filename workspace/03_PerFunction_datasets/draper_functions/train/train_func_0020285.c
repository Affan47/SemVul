e2_fs_is_dir (FileInfo *info, ViewInfo *view)
{

	if ( S_ISDIR (info->statbuf.st_mode) )
		return TRUE;
	if ( S_ISLNK(info->statbuf.st_mode) )
	{
		struct stat statbuf;
		gchar *localpath = e2_utils_dircat (view, info->filename, TRUE);
#ifdef E2_VFS
		VPATH data = { localpath, view->spacedata };
		gboolean ok = !e2_fs_stat (&data, &statbuf E2_ERR_NONE());
#else
		gboolean ok = !e2_fs_stat (localpath, &statbuf E2_ERR_NONE());
#endif
		g_free (localpath);
		if (ok && S_ISDIR (statbuf.st_mode))
		  return TRUE;
	}
	return FALSE;
}
