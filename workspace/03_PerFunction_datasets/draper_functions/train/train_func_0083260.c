tree_view_destroy (GtkObject * object) {

  AmitkTreeView * tree_view;

  g_return_if_fail (object != NULL);
  g_return_if_fail (AMITK_IS_TREE_VIEW (object));

  tree_view =  AMITK_TREE_VIEW (object);

  if (tree_view->current_path != NULL) {
    gtk_tree_path_free(tree_view->current_path);
    tree_view->current_path = NULL;
  }

  if (tree_view->active_object != NULL) {
    tree_view->active_object = amitk_object_unref(tree_view->active_object);
  }

  if (tree_view->study != NULL) {
    tree_view_remove_object(tree_view, AMITK_OBJECT(tree_view->study));
    tree_view->study = NULL;
  }

  if (tree_view->preferences != NULL) {
    g_object_unref(tree_view->preferences);
    tree_view->preferences = NULL;
  }

  if (tree_view->progress_dialog != NULL) {
    g_object_unref(tree_view->progress_dialog);
    tree_view->progress_dialog = NULL;
  }

  if (tree_view->drag_list != NULL) {
    gtk_target_list_unref (tree_view->drag_list);
    tree_view->drag_list = NULL;
  }

  if (GTK_OBJECT_CLASS (parent_class)->destroy)
    (* GTK_OBJECT_CLASS (parent_class)->destroy) (object);
}
