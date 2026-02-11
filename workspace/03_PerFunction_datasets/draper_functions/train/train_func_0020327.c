gc_prop_activate(GcomprisProperties *props)
{
  char *tmp;

  if (!g_file_test(props->config_dir, G_FILE_TEST_IS_DIR))
    gc_util_create_rootdir(props->config_dir);

  if (!g_file_test(props->user_dir, G_FILE_TEST_IS_DIR))
    gc_util_create_rootdir(props->user_dir);

  tmp = g_strconcat(props->user_dir, "/Images", NULL);
  if (!g_file_test(tmp, G_FILE_TEST_IS_DIR))
    gc_util_create_rootdir(tmp);
  g_free(tmp);

  tmp = g_strconcat(props->user_dir, "/", _("readme"), ".txt", NULL);
  g_file_set_contents(tmp,
		      _("This directory contains the files you create with the GCompris educational suite\n"),
		      -1,
		      NULL);
  g_free(tmp);

  tmp = g_strconcat(props->user_dir, "/Images/", _("readme"), ".txt", NULL);
  g_file_set_contents(tmp,
		      _("Put any number of images in this directory.\n"
			"You can include these images in your drawings and animations.\n"
			"The image formats supported are jpeg, png and svg.\n"),
		      -1,
		      NULL);
  g_free(tmp);

}
