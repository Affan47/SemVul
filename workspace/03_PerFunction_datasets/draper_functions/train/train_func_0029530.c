clutter_backend_dispose (GObject *gobject)
{
  ClutterBackendPrivate *priv = CLUTTER_BACKEND (gobject)->priv;


  _clutter_clear_events_queue ();


  if (priv->event_translators != NULL)
    {
      g_list_free (priv->event_translators);
      priv->event_translators = NULL;
    }

  G_OBJECT_CLASS (clutter_backend_parent_class)->dispose (gobject);
}
