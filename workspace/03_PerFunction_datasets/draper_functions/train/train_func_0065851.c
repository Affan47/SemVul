run_syntax_plugin_by_ftype(PluginManager *plugmg, Documentable *document)
{
  g_return_val_if_fail (OBJECT_IS_PLUGIN_MANAGER(plugmg), FALSE);
  PluginManagerDetails *plugmgdet;
  plugmgdet = PLUGIN_MANAGER_GET_PRIVATE(plugmg);
  gint ftype;
  g_object_get(document, "type", &ftype, NULL);
  Plugin *plug = g_hash_table_find (plugmgdet->plugins_table, get_syntax_plugin_by_ftype, GINT_TO_POINTER(ftype));
  if (plug){
    gphpedit_debug_message(DEBUG_PLUGINS,"%s","Plugin FOUND!!\n");
    plugin_run(plug, document);
    return TRUE;
  } else {
    gphpedit_debug_message(DEBUG_PLUGINS,"%s","Plugin NOT FOUND!!\n");
    return FALSE;
  }
}
