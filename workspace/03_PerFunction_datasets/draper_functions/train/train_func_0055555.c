get_book_codepoint_list (GucharmapChaptersModel *chapters)
{
  GucharmapChaptersModelPrivate *priv = chapters->priv;

  if (priv->book_list == NULL)
    {
      GtkTreeModel *model = GTK_TREE_MODEL (chapters);

      priv->book_list = gucharmap_script_codepoint_list_new ();
      gtk_tree_model_foreach (model, (GtkTreeModelForeachFunc) append_script, priv->book_list);
    }

  return g_object_ref (priv->book_list);
}
