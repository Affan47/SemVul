grl_flickr_source_browse (GrlSource *source,
                          GrlSourceBrowseSpec *bs)
{
  if (GRL_FLICKR_SOURCE (source)->priv->user_id) {
    grl_flickr_source_personal_browse (source, bs);
  } else {
    grl_flickr_source_public_browse (source, bs);
  }
}
