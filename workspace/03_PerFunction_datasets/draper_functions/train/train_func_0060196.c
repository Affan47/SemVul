save_actions()
{

  check_dirs();

  gchar* path = g_build_filename(g_get_user_data_dir(), ACTIONS_FILE, NULL);
  FILE* actions_file = fopen(path, "wb");
  g_free(path);

  if (actions_file)
  {
    GtkTreeIter action_iter;

    if (gtk_tree_model_get_iter_first((GtkTreeModel*)actions_list, &action_iter))
    {
      do
      {

        gchar *name, *command;
        gtk_tree_model_get((GtkTreeModel*)actions_list, &action_iter, 0, &name, 1, &command, -1);
        GString* s_name = g_string_new(name);
        GString* s_command = g_string_new(command);
        g_free(name);
        g_free(command);

        if ((s_name->len == 0) || (s_command->len == 0))
        {

          g_string_free(s_name, TRUE);
          g_string_free(s_command, TRUE);
          continue;
        }
        else
        {

          fwrite(&(s_name->len), 4, 1, actions_file);
          fputs(s_name->str, actions_file);
          fwrite(&(s_command->len), 4, 1, actions_file);
          fputs(s_command->str, actions_file);

          g_string_free(s_name, TRUE);
          g_string_free(s_command, TRUE);
        }
      }
      while(gtk_tree_model_iter_next((GtkTreeModel*)actions_list, &action_iter));
    }

    gint end = 0;
    fwrite(&end, 4, 1, actions_file);
    fclose(actions_file);
  }
}
