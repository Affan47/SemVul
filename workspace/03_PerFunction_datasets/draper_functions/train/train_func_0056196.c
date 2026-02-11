gst_gnome_vfs_location_to_uri_string (const gchar * location)
{
  gchar *newloc, *ret;

  if (location == NULL)
    return NULL;


  if (strstr (location, "://"))
    return g_strdup (location);

  newloc = gnome_vfs_escape_path_string (location);

  if (newloc && *newloc == '/') {
    ret = g_strdup_printf ("file://%s", newloc);
  } else {
    gchar *curdir;

    curdir = g_get_current_dir ();
    ret = g_strdup_printf ("file://%s/%s", curdir, newloc);
    g_free (curdir);
  }

  g_free (newloc);
  return ret;
}
