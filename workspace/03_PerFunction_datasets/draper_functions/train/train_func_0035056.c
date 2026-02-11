clutter_gst_auto_video_sink_dispose (GObject * object)
{
  ClutterGstAutoVideoSink *bin = CLUTTER_GST_AUTO_VIDEO_SINK (object);

  GST_DEBUG_OBJECT (bin, "Disposing");

  if (bin->child) {
    gst_element_set_state (bin->child, GST_STATE_NULL);
    gst_object_unref (bin->child);
    bin->child = NULL;
  }

  if (bin->sink_block_pad) {
    gst_object_unref (bin->sink_block_pad);
    bin->sink_block_pad = NULL;
  }

  bin->texture = NULL;

  G_OBJECT_CLASS (parent_class)->dispose ((GObject *) object);
}
