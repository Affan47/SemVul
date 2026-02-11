g_mount_info_apply_prefix (GMountInfo  *info,
			   char       **path)
{
  GMountSpec *spec;

  spec = info->mount_spec;

  if (spec->mount_prefix != NULL &&
      spec->mount_prefix[0] != 0)
    {
      char *path_with_prefix;
      path_with_prefix = g_build_path ("/", spec->mount_prefix,
                                       *path, NULL);
      g_free (*path);
      *path = path_with_prefix;
    }

}
