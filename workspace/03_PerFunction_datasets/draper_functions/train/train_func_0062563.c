gnc_tree_view_account_save(GncTreeViewAccount *view,
                           AccountFilterDialog *fd,
                           GKeyFile *key_file, const gchar *group_name)
{
    bar_t bar;

    g_return_if_fail (key_file != NULL);
    g_return_if_fail (group_name != NULL);

    ENTER("view %p, key_file %p, group_name %s", view, key_file,
          group_name);

    g_key_file_set_integer(key_file, group_name, ACCT_TYPES,
                           fd->visible_types);
    g_key_file_set_boolean(key_file, group_name, SHOW_HIDDEN,
                           fd->show_hidden);
    g_key_file_set_boolean(key_file, group_name, SHOW_ZERO,
                           fd->show_zero_total);

    bar.key_file = key_file;
    bar.group_name = group_name;
    bar.count = 0;
    tree_save_selected_row(view, &bar);
    gtk_tree_view_map_expanded_rows(
        GTK_TREE_VIEW(view), (GtkTreeViewMappingFunc) tree_save_expanded_row,
        &bar);
    g_key_file_set_integer(key_file, group_name, ACCT_COUNT, bar.count);
    LEAVE(" ");

}
