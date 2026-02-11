emerillon_sidebar_is_empty (EmerillonSidebar *sidebar)
{
  g_return_val_if_fail (EMERILLON_IS_SIDEBAR (sidebar), TRUE);

  return gtk_tree_model_iter_n_children (
      GTK_TREE_MODEL (sidebar->priv->page_model), NULL) == 0;
}
