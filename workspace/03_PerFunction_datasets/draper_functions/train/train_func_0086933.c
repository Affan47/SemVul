e2_fs_get_file_contents (VPATH *localpath, gpointer *contents,
	 gulong *contlength, gboolean string E2_ERR_ARG())
{
	gboolean retval;
#ifdef E2_VFS
	if (e2_fs_item_is_mounted (localpath))
	{
#endif
		struct stat sb;
		retval = TRUE;
		const gchar *fmt = NULL;
		gint fdesc = e2_fs_safeopen (VPCSTR(localpath), O_RDONLY, 0);
		if (fdesc >= 0)
		{
			if (!e2_fs_fstat (fdesc, &sb))
			{
				size_t len = sb.st_size;
				if (string)
					len += sizeof (gchar);


				*contents = g_try_malloc (len);
				if (*contents == NULL)
				{
					e2_utils_show_memory_message ();
#ifdef E2_VFSTMP


#endif
					e2_fs_safeclose (fdesc);
					return FALSE;
				}

				gulong nread = e2_fs_read (fdesc, *contents, sb.st_size E2_ERR_SAMEARG());
				if (nread < 0
				   )
				{
					g_free (*contents);
					*contents = NULL;
					nread = 0;
					retval = FALSE;
					fmt = _("Error reading file %s");
				}
				else if (string)
				{
					gchar *s;
					if (nread >= sizeof (gchar))
					{
						s = *contents + nread - sizeof (gchar);
						if (*s == '\0')
							nread -= sizeof (gchar);
						else
						{
							s += sizeof (gchar);
							*s = '\0';
						}
					}
					else
					{
						s = *contents;
						*s = '\0';
					}
				}

				if (contlength != NULL)
					*contlength = nread;
			}
			else
			{
				retval = FALSE;
				fmt = _("Cannot get information about %s");
			}
			e2_fs_safeclose (fdesc);
		}
		else
		{
			retval = FALSE;
			fmt = _("Cannot open file %s");
		}
#ifdef E2_VFS
	}
	else
	{
# ifdef E2_VFSTMP

# endif
		retval = FALSE;
		fmt = _("Error reading file %s");
	}
#endif
	if (!retval
		&& app.output.opt_show_on_new != NULL)

	{
		E2_ERR_BACKUP (localerr);
#ifdef E2_VFS
		e2_fs_set_error_from_errno (E2_ERR_NAME);
#endif
		e2_fs_error_local (fmt, localpath E2_ERR_MSGC());
		E2_ERR_CLEARBACKUP (localerr);
	}
	return retval;
}
