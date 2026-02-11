search_entry_changed_cb (GtkEntry           *entry,
                         GnomeControlCenter *center)
{
  GnomeControlCenterPrivate *priv = center->priv;
  char *str;


  if (!g_strcmp0 (priv->filter_string, gtk_entry_get_text (entry)))
    return;


  str = g_strdup (gtk_entry_get_text (entry));
  g_strstrip (str);
  if (!g_strcmp0 (str, priv->filter_string))
    {
      g_free (str);
      return;
    }

  g_free (priv->filter_string);
  priv->filter_string = str;

  if (!g_strcmp0 (priv->filter_string, ""))
    {
      shell_show_overview_page (center);
    }
  else
    {
      gtk_tree_model_filter_refilter (GTK_TREE_MODEL_FILTER (priv->search_filter));
      notebook_select_page (priv->notebook, priv->search_scrolled);
    }
}
