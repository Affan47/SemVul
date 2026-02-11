vfs_readdir (const gchar *path, gpointer buf, fuse_fill_dir_t filler, off_t offset,
             struct fuse_file_info *fi)
{
  GFile       *base_file;
  gint         result = 0;

  debug_print ("vfs_readdir: %s\n", path);

  if (path_is_mount_list (path))
    {
      GList *l;


      filler (buf, ".", NULL, 0);
      filler (buf, "..", NULL, 0);

      mount_list_lock ();

      for (l = mount_list; l; l = g_list_next (l))
        {
          MountRecord *mount_record = l->data;

          filler (buf, mount_record->name, NULL, 0);
        }

      mount_list_unlock ();
    }
  else if ((base_file = file_from_full_path (path)))
    {


      result = readdir_for_file (base_file, buf, filler);

      g_object_unref (base_file);
    }
  else
    {


      result = -ENOENT;
    }

  return result;
}
