g_vfs_backend_dav_uri_for_path (GVfsBackend *backend,
                                const char  *path,
                                gboolean     is_dir)
{
  SoupURI *mount_base;
  SoupURI *uri;
  char    *fn_encoded;
  char    *new_path;

  mount_base = http_backend_get_mount_base (backend);
  uri = soup_uri_copy (mount_base);


  if (!strcmp (path, "/"))
    return uri;


  fn_encoded = dav_uri_encode (path);


  if (is_dir == FALSE || g_str_has_suffix (path, "/"))
    new_path = g_build_path ("/", uri->path, fn_encoded, NULL);
  else
    new_path = g_build_path ("/", uri->path, fn_encoded, "/", NULL);

  g_free (fn_encoded);
  g_free (uri->path);
  uri->path = new_path;

  return uri;
}
