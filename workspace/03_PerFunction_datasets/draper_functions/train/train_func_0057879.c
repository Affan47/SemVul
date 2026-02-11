bacon_video_widget_get_deinterlacing (BaconVideoWidget * bvw)
{
  gint flags;

  g_return_val_if_fail (BACON_IS_VIDEO_WIDGET (bvw), FALSE);
  g_return_val_if_fail (GST_IS_ELEMENT (bvw->priv->play), FALSE);

  g_object_get (bvw->priv->play, "flags", &flags, NULL);

  return !!(flags & GST_PLAY_FLAG_DEINTERLACE);
}
