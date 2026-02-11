gst_rtsp_media_mapping_finalize (GObject * obj)
{
  GstRTSPMediaMapping *mapping = GST_RTSP_MEDIA_MAPPING (obj);

  GST_DEBUG_OBJECT (mapping, "finalized");

  g_hash_table_unref (mapping->mappings);

  G_OBJECT_CLASS (gst_rtsp_media_mapping_parent_class)->finalize (obj);
}
