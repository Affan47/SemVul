create_stream_liststore() {
  GtkListStore *ls;
  GtkWidget *tv;
  GtkCellRenderer *rend;
  GtkTreeViewColumn *col;

  if(glurp->gui_stream_list) {
    debug("Stream liststore exists, returning");
    return;
  }

  debug("Creating stream liststore...");

  ls = gtk_list_store_new(1, G_TYPE_STRING);
  tv = GTK_WIDGET(gtk_builder_get_object(builder, "streams_treeview"));

  gtk_tree_view_set_model(GTK_TREE_VIEW(tv), GTK_TREE_MODEL(ls));

  rend = gtk_cell_renderer_text_new();

  col = gtk_tree_view_column_new_with_attributes("#", rend,
                  "text", 0,
                  NULL);
  gtk_tree_view_column_set_sizing(col, GTK_TREE_VIEW_COLUMN_FIXED);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tv),col);

  glurp->gui_stream_list = ls;

  debug("Stream combobox model created");
}
