empathy_video_src_dispose (GObject *object)
{
  EmpathyGstVideoSrc *self = EMPATHY_GST_VIDEO_SRC (object);
  EmpathyGstVideoSrcPrivate *priv = EMPATHY_GST_VIDEO_SRC_GET_PRIVATE (self);

  if (priv->dispose_has_run)
    return;

  priv->dispose_has_run = TRUE;


  if (G_OBJECT_CLASS (empathy_video_src_parent_class)->dispose)
    G_OBJECT_CLASS (empathy_video_src_parent_class)->dispose (object);
}
