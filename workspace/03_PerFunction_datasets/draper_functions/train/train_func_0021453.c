exo_icon_chooser_dialog_entry_changed (GtkWidget            *combo,
                                       ExoIconChooserDialog *icon_chooser_dialog)
{
  ExoIconChooserDialogPrivate *priv = EXO_ICON_CHOOSER_DIALOG_GET_PRIVATE (icon_chooser_dialog);
  const gchar                 *text;
  gchar                       *normalized;
  GtkTreeModel                *model;

  g_free (priv->casefolded_text);
  priv->casefolded_text = NULL;

  text = gtk_entry_get_text (GTK_ENTRY (priv->filter_entry));
  if (!exo_str_is_empty (text))
    {

      normalized = g_utf8_normalize (text, -1, G_NORMALIZE_ALL);
      priv->casefolded_text = g_utf8_casefold (normalized, -1);
      g_free (normalized);
    }

#if GTK_CHECK_VERSION (2, 16, 0)
  gtk_entry_set_icon_sensitive (GTK_ENTRY (priv->filter_entry),
                                GTK_ENTRY_ICON_SECONDARY,
                                !exo_str_is_empty (text));
#endif

  model = exo_icon_view_get_model (EXO_ICON_VIEW (priv->icon_chooser));
  if (G_LIKELY (model != NULL))
    gtk_tree_model_filter_refilter (GTK_TREE_MODEL_FILTER (model));
}
