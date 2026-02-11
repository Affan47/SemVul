make_startup_plugin_list_for_editing(World *world)
{
  GSList      *pluginitem;
  GtkTreeIter  iter;

  pluginitem = world->startup_plugin_files;
  while (pluginitem) {
    gtk_list_store_append(GTK_LIST_STORE(world->startup_plugins), &iter);
    gtk_list_store_set(GTK_LIST_STORE(world->startup_plugins), &iter,
                       SPLUGIN_FILE, pluginitem->data,
                       -1);

    g_free(pluginitem->data);
    pluginitem = pluginitem->next;
  }
  g_slist_free(world->startup_plugin_files);
}
