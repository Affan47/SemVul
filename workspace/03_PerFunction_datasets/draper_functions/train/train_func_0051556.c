dav_uri_from_dns_sd_resolver (GVfsBackendDav *dav_backend)
{
  SoupURI    *uri;
  char       *user;
  char       *path;
  char       *address;
  const char *service_type;
  guint       port;

  service_type = g_vfs_dns_sd_resolver_get_service_type (dav_backend->resolver);
  address = g_vfs_dns_sd_resolver_get_address (dav_backend->resolver);
  port = g_vfs_dns_sd_resolver_get_port (dav_backend->resolver);
  user = g_vfs_dns_sd_resolver_lookup_txt_record (dav_backend->resolver, "u");
  path = g_vfs_dns_sd_resolver_lookup_txt_record (dav_backend->resolver, "path");


  uri = soup_uri_new (NULL);

  if (strcmp (service_type, "_webdavs._tcp") == 0)
    soup_uri_set_scheme (uri, SOUP_URI_SCHEME_HTTPS);
  else
    soup_uri_set_scheme (uri, SOUP_URI_SCHEME_HTTP);

  soup_uri_set_user (uri, user);

  soup_uri_set_port (uri, port);

  soup_uri_set_host (uri, address);

  if (path != NULL)
    soup_uri_set_path (uri, path);
  else
    soup_uri_set_path (uri, "/");


  g_free (address);
  g_free (user);
  g_free (path);

  return uri;
}
