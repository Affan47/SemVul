clutter_click_action_dispose (GObject *gobject)
{
  ClutterClickActionPrivate *priv = CLUTTER_CLICK_ACTION (gobject)->priv;

  if (priv->event_id)
    {
      g_signal_handler_disconnect (clutter_actor_meta_get_actor (CLUTTER_ACTOR_META (gobject)),
                                   priv->event_id);
      priv->event_id = 0;
    }

  if (priv->capture_id)
    {
      g_signal_handler_disconnect (priv->stage, priv->capture_id);
      priv->capture_id = 0;
    }

  if (priv->long_press_id)
    {
      g_source_remove (priv->long_press_id);
      priv->long_press_id = 0;
    }

  G_OBJECT_CLASS (clutter_click_action_parent_class)->dispose (gobject);
}
