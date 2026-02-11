gst_gsettings_video_sink_finalize (GObject * object)
{
  GstGSettingsVideoSink *sink = GST_GSETTINGS_VIDEO_SINK (object);

  g_free (sink->gsettings_str);
  g_main_context_unref (sink->context);

  GST_CALL_PARENT (G_OBJECT_CLASS, finalize, ((GObject *) (sink)));
}
