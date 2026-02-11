get_buffer (ClutterText *self)
{
  ClutterTextPrivate *priv = self->priv;

  if (priv->buffer == NULL)
    {
      ClutterTextBuffer *buffer;
      buffer = clutter_text_buffer_new ();
      clutter_text_set_buffer (self, buffer);
      g_object_unref (buffer);
    }

  return priv->buffer;
}
