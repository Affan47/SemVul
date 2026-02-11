has_action_by_name(const gchar * name)
{
    gchar *action_name = NULL;
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter)) {
        do {
            get_list_row(&iter, &action_name, NULL);
            if (g_str_equal(name, action_name))
                break;

            g_free(action_name);
            action_name = NULL;
        } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter));
    }

    g_free(action_name);
    return action_name != NULL;
}
