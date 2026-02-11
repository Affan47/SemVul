gdict_source_chooser_set_current_source (GdictSourceChooser *chooser,
                                         const gchar        *source_name)
{
  GdictSourceChooserPrivate *priv;
  SelectData data;
  gboolean retval;

  g_return_val_if_fail (GDICT_IS_SOURCE_CHOOSER (chooser), FALSE);
  g_return_val_if_fail (source_name != NULL, FALSE);

  priv = chooser->priv;

  if (priv->current_source && !strcmp (priv->current_source, source_name))
    return TRUE;

  data.source_name = g_strdup (source_name);
  data.chooser = chooser;
  data.found = FALSE;
  data.do_select = TRUE;
  data.do_activate = TRUE;

  gtk_tree_model_foreach (GTK_TREE_MODEL (priv->store),
                          scan_for_source_name,
                          &data);

  retval = data.found;

  GDICT_NOTE (CHOOSER, "%s current source: %s",
              data.found ? "set" : "not set",
              data.source_name);

  if (data.found)
    {
      g_free (priv->current_source);
      priv->current_source = data.source_name;
    }
  else
    g_free (data.source_name);

  return retval;
}
