glade_inspector_visible_func (GtkTreeModel *model,
                              GtkTreeIter *parent,
                              gpointer data)
{
  GladeInspector *inspector = data;
  GladeInspectorPrivate *priv = inspector->priv;

  GtkTreeIter iter;

  gboolean retval = FALSE;

  if (priv->search_disabled || priv->completion_text == NULL)
    return TRUE;

  if (gtk_tree_model_iter_children (model, &iter, parent))
    {
      do
        {
          retval = glade_inspector_visible_func (model, &iter, data);
        }
      while (gtk_tree_model_iter_next (model, &iter) && !retval);
    }

  if (!retval)
    {
      gchar *widget_name;

      gtk_tree_model_get (model, parent, GLADE_PROJECT_MODEL_COLUMN_NAME,
                          &widget_name, -1);

      retval = find_in_string_insensitive (widget_name, priv->completion_text);

      g_free (widget_name);
    }

  return retval;
}
