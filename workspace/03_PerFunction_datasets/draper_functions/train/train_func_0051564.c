e2_fs_set_file_contents (VPATH *localpath, gpointer contents,
	size_t contlength, mode_t mode E2_ERR_ARG())
{
	gboolean retval;
#ifdef E2_VFS
	if (e2_fs_item_is_mounted (localpath))
	{
#endif
		retval = TRUE;
		const gchar *fmt = NULL;
		gint fdesc = e2_fs_safeopen (VPCSTR(localpath), O_WRONLY | O_CREAT, mode);
		if (fdesc < 0)
		{
			retval = FALSE;
			fmt = _("Cannot create file %s");
		}

		if (retval)
		{
			ssize_t written = 0;
			while (written < contlength)
			{
				written = TEMP_FAILURE_RETRY (write (fdesc, contents, contlength));
				if (written < 0)
				{
					retval = FALSE;
					fmt = _("Error writing file %s");
					break;
				}
			}
			if (retval)
				ftruncate (fdesc, written);
			e2_fs_safeclose (fdesc);
		}

		if (!retval)
		{

			E2_ERR_BACKUP (localerr);
#ifdef E2_VFS
			e2_fs_set_error_from_errno (E2_ERR_NAME);
#endif
			e2_fs_error_local (fmt, localpath E2_ERR_MSGC());
			E2_ERR_CLEARBACKUP (localerr);
			unlink (VPCSTR(localpath));
		}
#ifdef E2_VFS
	}
	else
	{
# ifdef E2_VFSTMP

# endif
		retval = FALSE;
	}
#endif
	return retval;
}
