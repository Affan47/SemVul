make_thumbnail_fail_dirs (GnomeDesktopThumbnailFactory *factory)
{
  char *thumbnail_dir;
  char *fail_dir;
  char *app_dir;
  gboolean res;

  res = FALSE;

  thumbnail_dir = thumbnail_factory_build_filename (factory, NULL);
  if (!g_file_test (thumbnail_dir, G_FILE_TEST_IS_DIR))
    {
      g_mkdir (thumbnail_dir, 0700);
      res = TRUE;
    }

  fail_dir = g_build_filename (thumbnail_dir,
			       "fail",
			       NULL);
  if (!g_file_test (fail_dir, G_FILE_TEST_IS_DIR))
    {
      g_mkdir (fail_dir, 0700);
      res = TRUE;
    }

  app_dir = g_build_filename (fail_dir,
			      appname,
			      NULL);
  if (!g_file_test (app_dir, G_FILE_TEST_IS_DIR))
    {
      g_mkdir (app_dir, 0700);
      res = TRUE;
    }

  g_free (thumbnail_dir);
  g_free (fail_dir);
  g_free (app_dir);

  return res;
}
