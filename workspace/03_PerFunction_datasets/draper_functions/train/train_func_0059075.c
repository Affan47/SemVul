lookup_mount_info_by_fuse_path_in_cache (const char *fuse_path,
					 char **mount_path)
{
  GMountInfo *info;
  GList *l;

  G_LOCK (mount_cache);
  info = NULL;
  for (l = the_vfs->mount_cache; l != NULL; l = l->next)
    {
      GMountInfo *mount_info = l->data;

      if (mount_info->fuse_mountpoint != NULL &&
	  g_str_has_prefix (fuse_path, mount_info->fuse_mountpoint))
	{
	  int len = strlen (mount_info->fuse_mountpoint);
	  if (fuse_path[len] == 0 ||
	      fuse_path[len] == '/')
	    {
	      if (fuse_path[len] == 0)
		*mount_path = g_strdup ("/");
	      else
		*mount_path = g_strdup (fuse_path + len);
	      info = g_mount_info_ref (mount_info);
	      break;
	    }
	}
    }
  G_UNLOCK (mount_cache);

  return info;
}
