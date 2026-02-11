_e2pcr_get_tempname (VPATH *localpath, gchar *custom)
{
	gchar *temppath, *s;
	guint i = 0;
	E2_ERR_DECLARE
#ifdef E2_VFS
	VPATH tdata;
	tdata.spacedata = localpath->spacedata;
#endif
	while (TRUE)
	{
		temppath = g_strdup_printf ("%s%s~%d", VPSTR(localpath), custom, i);
		if (i == 0)
		{
			s = strrchr (temppath, '~');
			*s = '\0';
		}
#ifdef E2_VFS
		tdata.localpath = temppath;
		if (e2_fs_access2 (&tdata E2_ERR_PTR()) && E2_ERR_IS (ENOENT))
#else
		if (e2_fs_access2 (temppath E2_ERR_PTR()) && E2_ERR_IS (ENOENT))
#endif
		{
			E2_ERR_CLEAR
			break;
		}
		E2_ERR_CLEAR
		g_free (temppath);
		i++;
	}
	return temppath;
}
