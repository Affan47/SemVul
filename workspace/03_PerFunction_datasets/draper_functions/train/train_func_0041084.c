glade_project_drag_data_get (GtkTreeDragSource *drag_source,
                             GtkTreePath       *path,
                             GtkSelectionData  *selection_data)
{
  GtkTreeIter iter;

  if (gtk_tree_model_get_iter (GTK_TREE_MODEL (drag_source), &iter, path))
    {
      GObject *object;

      gtk_tree_model_get (GTK_TREE_MODEL (drag_source), &iter,
                          GLADE_PROJECT_MODEL_COLUMN_OBJECT, &object,
                          -1);

      _glade_dnd_set_data (selection_data, object);
      return TRUE;
    }

  return FALSE;
}
