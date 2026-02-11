http_from_uri (GVfsUriMapper  *mapper,
               const char     *uri_str,
               char          **path)
{
  GMountSpec *spec;
  gboolean ssl;
  GDecodedUri *uri;

  uri = g_vfs_decode_uri (uri_str);

  if (uri == NULL)
    return NULL;

  if (!g_ascii_strncasecmp (uri->scheme, "http", 4))
    {
      spec = g_mount_spec_new ("http");
      g_mount_spec_set (spec, "uri", uri_str);
    }
  else
    {
      spec = g_mount_spec_new ("dav");
      ssl = !g_ascii_strcasecmp (uri->scheme, "davs");
      g_mount_spec_set (spec, "ssl", ssl ? "true" : "false");

      if (uri->host && *uri->host)
        g_mount_spec_set (spec, "host", uri->host);

      if (uri->userinfo && *uri->userinfo)
        g_mount_spec_set (spec, "user", uri->userinfo);


      if (uri->port != -1 && ! port_is_default_port (uri->port, ssl))
        {
          char *port = g_strdup_printf ("%d", uri->port);
          g_mount_spec_set (spec, "port", port);
          g_free (port);
        }
    }

  *path = uri->path;
  uri->path = NULL;
  g_vfs_decoded_uri_free (uri);

  return spec;
}
