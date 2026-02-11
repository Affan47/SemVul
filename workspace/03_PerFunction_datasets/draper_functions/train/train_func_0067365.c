delete_button_cb(GtkButton *btn, gpointer data)
{
  GtkTreeSelection *selection;
  GtkTreeModel     *model;
  GtkTreeIter       iter;
  GtkTreeIter       parent;
  char             *name;
  char             *file;
  GtkWidget        *msgdlg;
  gchar            *msg;

  selection = gtk_tree_view_get_selection(lstWorlds);
  if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    return;


  if (!gtk_tree_model_iter_parent(model, &parent, &iter)) {
    parent = iter;
  }

  gtk_tree_model_get(model, &parent,
                     COLUMN_NAME, &name,
                     COLUMN_FILE, &file,
                     -1);

  msg = g_strdup_printf("world '%s'", name);
  msgdlg = we_guied_confirm_delete_dialog_new(GTK_WINDOW(wndMain),
                                              1,
                                              msg, "");
  g_free(msg);

  if (gtk_dialog_run(GTK_DIALOG(msgdlg)) == GTK_RESPONSE_YES) {
    GtkTreeIter  child;
    char        *otherfile;

    unlink(file);


    otherfile = malloc(strlen(file) + 5);
    strcpy(otherfile, file);
    strcat(otherfile, ".hst");
    unlink(otherfile);

    strcpy(otherfile, file);
    strcat(otherfile, ".var");
    unlink(otherfile);
    g_free(otherfile);


    if (gtk_tree_model_iter_children(model, &child, &parent)) {
      while (gtk_tree_store_remove(GTK_TREE_STORE(model), &child))
        ;
    }

    gtk_tree_store_remove(GTK_TREE_STORE(model), &parent);
  }
  gtk_widget_destroy(msgdlg);

  g_free(file);
}
