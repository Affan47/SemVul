plot_tree_display (ggobid * gg)
{
  GList *dlist;
  displayd *display;

  GtkWidget *tree, *sw;
  GtkWidget *plot_tree_window;
  GtkTreeModel *model;


  g_return_val_if_fail (gg->display_tree.tree == NULL, NULL);

  plot_tree_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (plot_tree_window), "GGobi Displays");
  gtk_window_set_default_size (GTK_WINDOW (plot_tree_window), 450, 200);

  model = GTK_TREE_MODEL (gtk_tree_store_new (DISPTREE_NCOLS, G_TYPE_STRING,
                                              G_TYPE_STRING, G_TYPE_STRING,
                                              G_TYPE_STRING, G_TYPE_OBJECT));

  g_signal_connect (G_OBJECT (gg),
                    "select_variable",
                    G_CALLBACK (update_display_tree_plots_by_variable),
                    (gpointer) model);

  gg->display_tree.model = model;
  for (dlist = gg->displays; dlist; dlist = dlist->next) {
    display = (displayd *) dlist->data;
    display_add_tree (display);
  }

  tree = gtk_tree_view_new_with_model (model);
  gg->display_tree.tree = tree;
  populate_tree_view (tree, disptree_lbl, G_N_ELEMENTS (disptree_lbl), true,
                      GTK_SELECTION_SINGLE,
                      G_CALLBACK (display_tree_child_select), NULL);

  sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (sw), tree);
  gtk_container_add (GTK_CONTAINER (plot_tree_window), sw);
  gtk_widget_show_all (plot_tree_window);


  g_signal_connect (G_OBJECT (plot_tree_window), "delete_event",
                    G_CALLBACK (display_tree_delete_cb), gg);

  gg->display_tree.window = plot_tree_window;

  return (GTK_TREE_VIEW (tree));
}
