grl_flickr_source_resolve (GrlSource *source,
                           GrlSourceResolveSpec *rs)
{
  const gchar *id;

  if (!rs->media || (id = grl_media_get_id (rs->media)) == NULL) {
    rs->callback (rs->source, rs->operation_id,
                  rs->media, rs->user_data, NULL);
    return;
  }

  g_flickr_photos_getInfo (GRL_FLICKR_SOURCE (source)->priv->flickr,
                           id,
                           getInfo_cb,
                           rs);
}
