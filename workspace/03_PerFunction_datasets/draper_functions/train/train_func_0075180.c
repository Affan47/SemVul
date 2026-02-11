e2_fs_stat (VPATH *localpath, struct stat *buf E2_ERR_ARG())
{
#ifdef E2_VFS
# ifdef E2_VFSTMP

# endif
	if (e2_fs_item_is_mounted (localpath))
	{
#endif
		if (stat (VPCSTR(localpath), buf))
		{
			struct stat statbuf;
			if (!lstat (VPCSTR(localpath), &statbuf)

				&& (S_ISLNK (statbuf.st_mode) && errno == ENOENT))
			{
				*buf = statbuf;
				return 0;
			}
			return -1;
		}
		return 0;
#ifdef E2_VFS
	}
	else
	{
		gint result = -1;
		if (e2_fs_vfsfunc_ready ((gpointer *)&vfs.start_operation))
		{
			E2_VFSMonitor opdata;

			opdata.flags = E2VFS_TIMER | E2VFS_CANCEL;
			if (vfs.start_operation (localpath->spacedata, IFACE_OFFSET (stat), &opdata))
			{
				opdata.error = E2_ERR_NAME;
				result = opdata.iface->stat (localpath, buf, &opdata);
				vfs.finish_operation (&opdata);
			}
		}
		return result;
	}
#endif
}
