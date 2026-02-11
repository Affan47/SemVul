getattr_for_file (GFile *file, struct stat *sbuf)
{
  GFileInfo *file_info;
  GError    *error  = NULL;
  gint       result = 0;

  file_info = g_file_query_info (file,
                                 G_FILE_ATTRIBUTE_STANDARD_TYPE ","
                                 G_FILE_ATTRIBUTE_STANDARD_NAME ","
                                 G_FILE_ATTRIBUTE_STANDARD_IS_SYMLINK ","
                                 G_FILE_ATTRIBUTE_STANDARD_SIZE ","
                                 G_FILE_ATTRIBUTE_UNIX_MODE ","
                                 G_FILE_ATTRIBUTE_TIME_CHANGED ","
                                 G_FILE_ATTRIBUTE_TIME_MODIFIED ","
                                 G_FILE_ATTRIBUTE_TIME_ACCESS ","
                                 G_FILE_ATTRIBUTE_UNIX_BLOCK_SIZE ","
                                 G_FILE_ATTRIBUTE_UNIX_BLOCKS ","
				 "access::*",
                                 0, NULL, &error);

  if (file_info)
    {
      GTimeVal mod_time;

      sbuf->st_mode = file_info_get_stat_mode (file_info);
      sbuf->st_size = g_file_info_get_size (file_info);
      sbuf->st_uid = daemon_uid;
      sbuf->st_gid = daemon_gid;

      g_file_info_get_modification_time (file_info, &mod_time);
      sbuf->st_mtime = mod_time.tv_sec;
      sbuf->st_ctime = mod_time.tv_sec;
      sbuf->st_atime = mod_time.tv_sec;

      if (g_file_info_has_attribute (file_info, G_FILE_ATTRIBUTE_TIME_CHANGED))
        sbuf->st_ctime = file_info_get_attribute_as_uint (file_info, G_FILE_ATTRIBUTE_TIME_CHANGED);
      if (g_file_info_has_attribute (file_info, G_FILE_ATTRIBUTE_TIME_ACCESS))
        sbuf->st_atime = file_info_get_attribute_as_uint (file_info, G_FILE_ATTRIBUTE_TIME_ACCESS);

      if (g_file_info_has_attribute (file_info, G_FILE_ATTRIBUTE_UNIX_BLOCK_SIZE))
	sbuf->st_blksize = file_info_get_attribute_as_uint (file_info, G_FILE_ATTRIBUTE_UNIX_BLOCK_SIZE);
      if (g_file_info_has_attribute (file_info, G_FILE_ATTRIBUTE_UNIX_BLOCKS))
	sbuf->st_blocks = file_info_get_attribute_as_uint (file_info, G_FILE_ATTRIBUTE_UNIX_BLOCKS);
      else
	sbuf->st_blocks = (sbuf->st_size + 511) / 512;


      sbuf->st_nlink = 1;

      g_object_unref (file_info);
    }
  else
    {
      if (error)
        {
          debug_print ("Error from GVFS: %s\n", error->message);
          result = -errno_from_error (error);
          g_error_free (error);
        }
      else
        {
          debug_print ("No file info, but no error from GVFS.\n");
          result = -EIO;
        }
    }

  return result;
}
