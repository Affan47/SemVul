gst_app_src_set_stream_type (GstAppSrc * appsrc, GstAppStreamType type)
{
  GstAppSrcPrivate *priv;

  g_return_if_fail (GST_IS_APP_SRC (appsrc));

  priv = appsrc->priv;

  GST_OBJECT_LOCK (appsrc);
  GST_DEBUG_OBJECT (appsrc, "setting stream_type of %d", type);
  priv->stream_type = type;
  GST_OBJECT_UNLOCK (appsrc);
}
