clutter_text_dirty_paint_volume (ClutterText *text)
{
  ClutterTextPrivate *priv = text->priv;

  if (priv->paint_volume_valid)
    {
      clutter_paint_volume_free (&priv->paint_volume);
      priv->paint_volume_valid = FALSE;
    }
}
