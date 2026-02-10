asset_loaded_cb (GObject * source, GAsyncResult * res, GMainLoop * mainloop)
{
  GESUriClipAsset *mfs =
      GES_URI_CLIP_ASSET (ges_asset_request_finish (res, NULL));
  GstDiscovererInfo *discoverer_info = NULL;
  discoverer_info = ges_uri_clip_asset_get_info (mfs);

  GST_DEBUG ("Result is %d", gst_discoverer_info_get_result (discoverer_info));
  GST_DEBUG ("Info type is %s", G_OBJECT_TYPE_NAME (mfs));
  GST_DEBUG ("Duration is %" GST_TIME_FORMAT,
      GST_TIME_ARGS (ges_uri_clip_asset_get_duration (mfs)));

  gst_object_unref (mfs);

  g_main_loop_quit (mainloop);
}
