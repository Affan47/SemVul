photos_flickr_item_open (PhotosBaseItem *item, GdkScreen *screen, guint32 timestamp)
{
  PhotosFlickrItem *self = PHOTOS_FLICKR_ITEM (item);
  PhotosFlickrItemPrivate *priv = self->priv;
  GError *error;
  GoaAccount *account;
  GoaObject *object;
  PhotosSource *source;
  const gchar *identifier;
  const gchar *identity;
  const gchar *resource_urn;
  gchar *flickr_uri;

  identifier = photos_base_item_get_identifier (item) + strlen ("flickr:");

  resource_urn = photos_base_item_get_resource_urn (item);
  source = PHOTOS_SOURCE (photos_base_manager_get_object_by_id (priv->src_mngr, resource_urn));
  object = photos_source_get_goa_object (source);
  account = goa_object_peek_account (object);
  identity = goa_account_get_identity (account);

  flickr_uri = g_strdup_printf ("https://www.flickr.com/photos/%s/%s", identity, identifier);

  error = NULL;
  gtk_show_uri (screen, flickr_uri, timestamp, &error);
  if (error != NULL)
    {
      g_warning ("Unable to show URI %s: %s", flickr_uri, error->message);
      g_error_free (error);
    }

  g_free (flickr_uri);
}
