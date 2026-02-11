dst_key_press_callback(GtkWidget *w, GdkEventKey *ev,
				       gpointer data)
{
  GtkTreeModel *model;
  struct worklist_data *ptr;

  ptr = data;
  model = GTK_TREE_MODEL(ptr->dst);

  if (ev->keyval == GDK_Delete) {
    GtkTreeIter it, it_next;
    bool deleted = FALSE;

    if (gtk_tree_model_get_iter_first(model, &it)) {
      bool more;

      do {
	it_next = it;
	more = gtk_tree_model_iter_next(model, &it_next);

	if (gtk_tree_selection_iter_is_selected(ptr->dst_selection, &it)) {
	  gtk_list_store_remove(GTK_LIST_STORE(model), &it);
	  deleted = TRUE;
	}
	it = it_next;

      } while (more);
    }

    if (deleted) {
      commit_worklist(ptr);
    }
    return TRUE;

  } else if ((ev->state & GDK_MOD1_MASK) && ev->keyval == GDK_Up) {
    queue_bubble_up(ptr);
    return TRUE;

  } else if ((ev->state & GDK_MOD1_MASK) && ev->keyval == GDK_Down) {
    queue_bubble_down(ptr);
    return TRUE;

  } else {
    return FALSE;
  }
}
