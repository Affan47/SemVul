vfs_getattr (const gchar *path, struct stat *sbuf)
{
  GFile      *file;
  gint        result = 0;

  debug_print ("vfs_getattr: %s\n", path);

  memset (sbuf, 0, sizeof (*sbuf));

  sbuf->st_dev = 0;
  sbuf->st_ino = 0;
  sbuf->st_uid = 0;
  sbuf->st_gid = 0;
  sbuf->st_rdev = 0;
  sbuf->st_size = 0;
  sbuf->st_blocks = 0;
  sbuf->st_atime = 0;
  sbuf->st_mtime = 0;
  sbuf->st_ctime = 0;
  sbuf->st_blksize = 4096;

  if (path_is_mount_list (path))
    {


      sbuf->st_mode = S_IFDIR | 0500;
      sbuf->st_nlink = 2 + g_list_length (mount_list);
      sbuf->st_atime = daemon_creation_time;
      sbuf->st_mtime = daemon_creation_time;
      sbuf->st_ctime = daemon_creation_time;
      sbuf->st_uid   = daemon_uid;
      sbuf->st_gid   = daemon_gid;
    }
  else if ((file = file_from_full_path (path)))
    {


      result = getattr_for_file (file, sbuf);

      if (result != 0)
        {
          FileHandle *fh = get_file_handle_for_path (path);


          if (fh != NULL)
            {
              g_mutex_lock (&fh->mutex);
              getattr_for_file_handle (fh, sbuf);
              g_mutex_unlock (&fh->mutex);

              file_handle_unref (fh);
              result = 0;
            }
        }

      g_object_unref (file);
    }
  else
    {
      result = -ENOENT;
    }

  debug_print ("vfs_getattr: -> %s\n", g_strerror (-result));

  return result;
}
