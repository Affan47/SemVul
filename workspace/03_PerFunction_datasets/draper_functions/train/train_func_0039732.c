reload_menu (GnomeControlCenter *shell)
{
  GError *error;
  GMenuTreeDirectory *d;
  GMenuTreeIter *iter;
  GMenuTreeItemType next_type;

  error = NULL;
  if (!gmenu_tree_load_sync (shell->priv->menu_tree, &error))
    {
      g_warning ("Could not load control center menu: %s", error->message);
      g_clear_error (&error);
      return;
    }


  d = gmenu_tree_get_root_directory (shell->priv->menu_tree);
  iter = gmenu_tree_directory_iter (d);

  while ((next_type = gmenu_tree_iter_next (iter)) != GMENU_TREE_ITEM_INVALID)
    {
      if (next_type == GMENU_TREE_ITEM_DIRECTORY)
        {
          GMenuTreeDirectory *subdir;
          const gchar *dir_name;
          GMenuTreeIter *sub_iter;
          GMenuTreeItemType sub_next_type;

          subdir = gmenu_tree_iter_get_directory (iter);
          dir_name = gmenu_tree_directory_get_name (subdir);

          maybe_add_category_view (shell, dir_name);


          sub_iter = gmenu_tree_directory_iter (subdir);
          while ((sub_next_type = gmenu_tree_iter_next (sub_iter)) != GMENU_TREE_ITEM_INVALID)
            {
              if (sub_next_type == GMENU_TREE_ITEM_ENTRY)
                {
                  GMenuTreeEntry *item = gmenu_tree_iter_get_entry (sub_iter);
                  cc_shell_model_add_item (CC_SHELL_MODEL (shell->priv->store),
                                           dir_name,
                                           item);
                  gmenu_tree_item_unref (item);
                }
            }

          gmenu_tree_iter_unref (sub_iter);
          gmenu_tree_item_unref (subdir);
        }
    }

  gmenu_tree_iter_unref (iter);
}
