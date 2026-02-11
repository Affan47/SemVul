gc_skin_image_get(gchar *pixmapfile)
{
  GcomprisProperties *properties = gc_prop_get();
  gchar *filename;


  filename = g_strdup_printf("%s/%s/%s",
			     properties->package_skin_dir,
			     properties->skin,
			     pixmapfile);

  if (g_file_test ((filename), G_FILE_TEST_EXISTS)) {
    g_free(filename);

    filename = g_strdup_printf("%s/%s", properties->skin, pixmapfile);

    return(filename);
  }
  g_free(filename);


  filename = g_strdup_printf("%s/%s", DEFAULT_SKIN, pixmapfile);
  return(filename);
}
