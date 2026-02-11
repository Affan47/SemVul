gdict_defbox_dispose (GObject *gobject)
{
  GdictDefbox *defbox = GDICT_DEFBOX (gobject);
  GdictDefboxPrivate *priv = defbox->priv;

  if (priv->start_id)
    {
      g_signal_handler_disconnect (priv->context, priv->start_id);
      g_signal_handler_disconnect (priv->context, priv->end_id);
      g_signal_handler_disconnect (priv->context, priv->define_id);

      priv->start_id = 0;
      priv->end_id = 0;
      priv->define_id = 0;
    }

  if (priv->error_id)
    {
      g_signal_handler_disconnect (priv->context, priv->error_id);
      priv->error_id = 0;
    }

  if (priv->context)
    {
      g_object_unref (priv->context);
      priv->context = NULL;
    }

  if (priv->buffer)
    {
      g_object_unref (priv->buffer);
      priv->buffer = NULL;
    }

  g_clear_object (&priv->busy_cursor);
  g_clear_object (&priv->hand_cursor);
  g_clear_object (&priv->regular_cursor);

  G_OBJECT_CLASS (gdict_defbox_parent_class)->dispose (gobject);
}
