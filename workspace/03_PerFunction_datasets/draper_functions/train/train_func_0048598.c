get_plugin_by_num(PluginManager *plugmg, gint num){
  g_return_val_if_fail (num<10, NULL);
  g_return_val_if_fail (OBJECT_IS_PLUGIN_MANAGER(plugmg), NULL);
  PluginManagerDetails *plugmgdet;
  plugmgdet = PLUGIN_MANAGER_GET_PRIVATE(plugmg);
  GList *pluglist = g_hash_table_get_values (plugmgdet->plugins_table);
  Plugin *plug= g_list_nth_data (pluglist,num);
  g_list_free (pluglist);
  return plug;
}
