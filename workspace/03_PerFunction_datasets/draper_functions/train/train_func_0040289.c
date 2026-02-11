column_toggled        (GtkCellRendererToggle *cell,
                 gchar                 *path_str,
                 gpointer               data)
{
     GtkSatListColSel *sel = GTK_SAT_LIST_COL_SEL (data);
     GtkTreeModel *model;
     GtkTreeIter   iter;
     GtkTreePath  *path = gtk_tree_path_new_from_string (path_str);
     gboolean      checked;
     gint          row;


     g_signal_handler_block (cell, sel->handler_id);


     model = gtk_tree_view_get_model (GTK_TREE_VIEW (sel->list));
     gtk_tree_model_get_iter (model, &iter, path);
     gtk_tree_model_get (model, &iter,
                   1, &checked,
                   2, &row,
                   -1);


     checked = !checked;

     gtk_list_store_set (GTK_LIST_STORE (model), &iter,
                   1, checked,
                   -1);

     if (checked) {

          sel->flags |= (1 << row);
     }
     else {

          sel->flags &= ~(1 << row);
     }


     gtk_tree_path_free (path);


     g_signal_handler_unblock (cell, sel->handler_id);

}
