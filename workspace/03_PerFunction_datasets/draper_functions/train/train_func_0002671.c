fsp_session_set_http_proxy              (FspSession *self,
                                         gboolean use_gnome_proxy,
                                         const char *host, const char *port,
                                         const char *username, const char *password)
{
  SoupURI *proxy_uri = NULL;

#ifdef HAVE_LIBSOUP_GNOME
  gboolean using_gnome_proxy_before = FALSE;
#endif

  g_return_val_if_fail (FSP_IS_SESSION (self), FALSE);

#ifdef HAVE_LIBSOUP_GNOME

  using_gnome_proxy_before = self->priv->using_gnome_proxy;

  if (using_gnome_proxy_before != use_gnome_proxy)
    {
      void (*soup_feature_func) (SoupSession *, GType) = NULL;
      if (use_gnome_proxy)
        soup_feature_func = soup_session_add_feature_by_type;
      else
        soup_feature_func = soup_session_remove_feature_by_type;


      soup_feature_func (self->priv->soup_session,
                         SOUP_TYPE_PROXY_RESOLVER_DEFAULT);
    }
  self->priv->using_gnome_proxy = use_gnome_proxy;
#else

  self->priv->using_gnome_proxy = FALSE;
#endif

  if (!self->priv->using_gnome_proxy)
    {

      if (host != NULL)
        {
          const gchar *actual_user = NULL;
          const gchar *actual_password = NULL;
          guint actual_port = 0;


          if (username == NULL || *username == '\0')
            actual_user = NULL;
          else
            actual_user = username;


          if (password == NULL || *password == '\0')
            actual_password = NULL;
          else
            actual_password = password;


          actual_port = (guint) g_ascii_strtoll ((gchar *) port, NULL, 10);


          proxy_uri = soup_uri_new (NULL);
          soup_uri_set_scheme (proxy_uri, SOUP_URI_SCHEME_HTTP);
          soup_uri_set_host (proxy_uri, host);
          soup_uri_set_port (proxy_uri, actual_port);
          soup_uri_set_user (proxy_uri, actual_user);
          soup_uri_set_password (proxy_uri, actual_password);
          soup_uri_set_path (proxy_uri, "");
        }
    }


  g_object_set (G_OBJECT (self->priv->soup_session),
                SOUP_SESSION_PROXY_URI,
                proxy_uri,
                NULL);


  if ((!self->priv->proxy_uri && proxy_uri)
      || (self->priv->proxy_uri && !proxy_uri)
      || (self->priv->proxy_uri && proxy_uri && !soup_uri_equal (self->priv->proxy_uri, proxy_uri)))
    {

      if (self->priv->proxy_uri)
        soup_uri_free (self->priv->proxy_uri);

      self->priv->proxy_uri = proxy_uri;


      return TRUE;
    }

#ifdef HAVE_LIBSOUP_GNOME
  return using_gnome_proxy_before != use_gnome_proxy;
#else

  return FALSE;
#endif
}
