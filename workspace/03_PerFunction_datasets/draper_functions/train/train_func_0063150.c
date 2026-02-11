chapters_view_selection_changed_cb (GtkTreeSelection *selection,
                                    GucharmapCharmap *charmap)
{
  GucharmapCharmapPrivate *priv = charmap->priv;
  GucharmapCodepointList *codepoint_list;
  GtkTreeIter iter;

  if (!gtk_tree_selection_get_selected (selection, NULL, &iter))
    return;

  codepoint_list = gucharmap_chapters_view_get_codepoint_list (priv->chapters_view);
  gucharmap_chartable_set_codepoint_list (priv->chartable, codepoint_list);
  g_object_unref (codepoint_list);

  g_object_notify (G_OBJECT (charmap), "active-chapter");
}
