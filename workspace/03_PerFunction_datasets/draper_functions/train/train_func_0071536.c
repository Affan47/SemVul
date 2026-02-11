bacon_video_widget_get_language (BaconVideoWidget * bvw)
{
  int language = -1;

  g_return_val_if_fail (BACON_IS_VIDEO_WIDGET (bvw), -1);
  g_return_val_if_fail (bvw->priv->play != NULL, -1);

  g_object_get (G_OBJECT (bvw->priv->play), "current-audio", &language, NULL);

  return language;
}
