bacon_video_widget_get_zoom (BaconVideoWidget *bvw)
{
  gboolean expand;

  g_return_val_if_fail (BACON_IS_VIDEO_WIDGET (bvw), 1.0);

  expand = totem_aspect_frame_get_expand (TOTEM_ASPECT_FRAME (bvw->priv->frame));
  return expand ? BVW_ZOOM_EXPAND : BVW_ZOOM_NONE;
}
