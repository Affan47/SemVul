clutter_backend_real_translate_event (ClutterBackend *backend,
                                      gpointer        native,
                                      ClutterEvent   *event)
{
  ClutterBackendPrivate *priv = backend->priv;
  GList *l;

  for (l = priv->event_translators;
       l != NULL;
       l = l->next)
    {
      ClutterEventTranslator *translator = l->data;
      ClutterTranslateReturn retval;

      retval = _clutter_event_translator_translate_event (translator,
                                                          native,
                                                          event);

      if (retval == CLUTTER_TRANSLATE_QUEUE)
        return TRUE;

      if (retval == CLUTTER_TRANSLATE_REMOVE)
        return FALSE;
    }

  return FALSE;
}
