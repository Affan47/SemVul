exo_die_command_model_collect_idle (gpointer user_data)
{
  ExoDieCommandModel *command_model = EXO_DIE_COMMAND_MODEL (user_data);
  GtkTreePath        *path;
  GtkTreeIter         iter;
  GSList             *lp;
  GSList             *np;

  g_return_val_if_fail (EXO_DIE_IS_COMMAND_MODEL (command_model), FALSE);
  g_return_val_if_fail (command_model->items == NULL, FALSE);

  GDK_THREADS_ENTER ();


  command_model->items = command_model->collect_items;
  command_model->collect_items = NULL;


  path = gtk_tree_path_new_first ();
  for (lp = command_model->items; lp != NULL; lp = lp->next)
    {

      np = lp->next;
      lp->next = NULL;


      iter.stamp = command_model->stamp;
      iter.user_data = lp;


      gtk_tree_model_row_inserted (GTK_TREE_MODEL (command_model), path, &iter);


      gtk_tree_path_next (path);


      lp->next = np;
    }
  gtk_tree_path_free (path);


  g_signal_emit (G_OBJECT (command_model), command_model_signals[LOADED], 0);

  GDK_THREADS_LEAVE ();

  return FALSE;
}
