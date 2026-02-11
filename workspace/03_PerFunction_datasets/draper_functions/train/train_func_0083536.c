on_presentity_removed (HeapView* self,
		       Ekiga::PresentityPtr presentity)
{
  GtkTreeModel* model;
  GtkTreeIter group_iter;
  GtkTreeIter iter;

  model = GTK_TREE_MODEL (self->priv->store);

  if (gtk_tree_model_get_iter_first (model, &group_iter)) {

    do {

      find_iter_for_presentity (self, presentity.get (), &group_iter, &iter);
      gtk_tree_store_remove (self->priv->store, &iter);
    } while (gtk_tree_model_iter_next (model, &group_iter));
  }

  clear_empty_groups (self);
}
