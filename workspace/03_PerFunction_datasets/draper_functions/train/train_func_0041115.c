ges_formatter_save_to_uri (GESFormatter * formatter, GESTimeline *
    timeline, gchar * uri)
{
  GESFormatterClass *klass = GES_FORMATTER_GET_CLASS (formatter);
  GList *layers, *tmp;


  layers = ges_timeline_get_layers (timeline);
  g_return_val_if_fail (layers != NULL, FALSE);
  for (tmp = layers; tmp; tmp = g_list_next (tmp)) {
    g_object_unref (tmp);
  }

  if (klass->save_to_uri)
    return klass->save_to_uri (formatter, timeline, uri);

  return FALSE;
}
