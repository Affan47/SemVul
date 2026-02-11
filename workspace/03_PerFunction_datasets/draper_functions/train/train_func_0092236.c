_e2p_touch (VPATH *localpath, E2_TouchData *data, gboolean recurse)
{
	struct stat statbuf;
	E2_ERR_DECLARE

	if (recurse)
	{

		if (e2_fs_stat (localpath, &statbuf E2_ERR_PTR()))
		{

			e2_fs_error_local (_("Cannot get current data for %s"),
				localpath E2_ERR_MSGL());
			E2_ERR_CLEAR
			return FALSE;
		}
		if (S_ISDIR (statbuf.st_mode))
		{


			data->dirdata = NULL;

			gboolean retval = e2_fs_tw (localpath, _e2_task_twcb_touch, data, -1,

				E2TW_FIXDIR | E2TW_MOUNT E2_ERR_PTR());

			if (data->dirdata != NULL)
			{
#ifdef E2_VFS
				VPATH ddata;
				ddata.spacedata = localpath->spacedata;
#endif
				GList *member;
				for (member = data->dirdata; member != NULL; member = member->next)
				{
					E2P_DirEnt *dirfix = member->data;
#ifdef E2_VFS
					ddata.localpath = dirfix->path;
					if (e2_fs_lstat (&ddata, &statbuf E2_ERR_NONE())
						|| !_e2pt_touch1 (&ddata, &statbuf, data))
#else
					if (e2_fs_lstat (dirfix->path, &statbuf E2_ERR_NONE())
						|| !_e2pt_touch1 (dirfix->path, &statbuf, data))
#endif
						retval = FALSE;
#ifdef E2_VFS
					if (e2_fs_chmod (&ddata, dirfix->mode E2_ERR_PTR())
#else
					if (e2_fs_chmod (dirfix->path, dirfix->mode E2_ERR_PTR())
#endif
						&& E2_ERR_ISNOT (ENOENT))
						e2_fs_error_local (_("Cannot change permissions of %s"),
							localpath E2_ERR_MSGL());
					E2_ERR_CLEAR
					g_free (dirfix->path);
					DEALLOCATE (E2P_DirEnt, dirfix);
				}
				g_list_free (data->dirdata);
			}

			if (!retval)
			{

				E2_ERR_CLEAR
			}
			return retval;
		}
		else
			recurse = FALSE;
	}
	if (!recurse)
	{

		if (e2_fs_lstat (localpath, &statbuf E2_ERR_PTR()))
		{
			e2_fs_error_local (_("Cannot get current times of %s"), localpath E2_ERR_MSGL());
			E2_ERR_CLEAR
			return FALSE;
		}
		return (_e2pt_touch1 (localpath, &statbuf, data));
	}
	return FALSE;
}
