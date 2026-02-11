_e2_fs_grep_file_output (VPATH *localpath, gchar *string E2_ERR_ARG())
{
#ifdef E2_VFS
	if (e2_fs_item_is_mounted (localpath))
	{
#endif
		gchar line[PATH_MAX + 20];


		gchar *local = F_FILENAME_TO_LOCALE (curr_view->dir);
#ifdef E2_VFS
		VPATH data = { local, NULL };
		if (e2_fs_chdir_local (&data E2_ERR_NONE()))
#else
		if (e2_fs_chdir_local (local E2_ERR_NONE()))
#endif
		{

			F_FREE (local);
			return FALSE;
		}
		F_FREE (local);

		size_t bsize = E2_MAX_LEN;
#ifdef USE_GLIB2_10
		gchar *buf = (gchar *) g_slice_alloc ((gulong) bsize);
#else
		gchar *buf = (gchar *) g_try_malloc ((gulong) bsize);
#endif
		CHECKALLOCATEDWARN (buf, return FALSE;);


		snprintf (line, sizeof (line), ("file \"%s\""),
			VPSTR(localpath));
		E2_FILE *pipe = e2_fs_open_pipe (line);
		if (pipe == NULL)
		{
#ifdef USE_GLIB2_10
			g_slice_free1 (bsize, buf);
#else
			g_free (buf);
#endif
			return FALSE;
		}
		gboolean retval = FALSE;
#ifdef __USE_GNU
		while (getdelim (&buf, &bsize, '\n', pipe) > 1)
#else
		while (fgets (buf, bsize, pipe) != NULL && *buf != '\n')
#endif
		{
			if (strstr (buf, string))
			{
				retval = TRUE;
				break;
			}
		}
		e2_fs_pipe_close (pipe);
#ifdef USE_GLIB2_10
		g_slice_free1 (bsize, buf);
#else
		g_free (buf);
#endif
		return retval;
#ifdef E2_VFS
	}
	else
	{


# ifdef E2_VFSTMP

# endif
		return FALSE;
	}
#endif
}
