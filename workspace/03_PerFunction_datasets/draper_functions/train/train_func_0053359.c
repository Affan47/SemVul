gupnp_resolve_result_cb (GUPnPDIDLLiteParser *parser,
                         GUPnPDIDLLiteObject *didl,
                         gpointer user_data)
{
  GrlSourceResolveSpec *rs = (GrlSourceResolveSpec *) user_data;

  if (gupnp_didl_lite_object_get_id (didl)) {
    build_media_from_didl (rs->media, didl, rs->keys);
    rs->callback (rs->source, rs->operation_id, rs->media, rs->user_data, NULL);
  }
}
