clutter_canvas_invalidate (ClutterContent *content)
{
  ClutterCanvas *self = CLUTTER_CANVAS (content);
  ClutterCanvasPrivate *priv = self->priv;

  if (priv->buffer != NULL)
    {
      cogl_object_unref (priv->buffer);
      priv->buffer = NULL;
    }

  if (priv->width <= 0 || priv->height <= 0)
    return;

  clutter_canvas_emit_draw (self);
}
