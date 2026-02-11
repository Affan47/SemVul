gdl_set_cursor (GladeDesignLayoutPrivate *priv, GdkCursor *cursor)
{
  if (cursor != priv->cursor)
    {
      priv->cursor = cursor;
      gdk_window_set_cursor (priv->window, cursor);
    }
}
