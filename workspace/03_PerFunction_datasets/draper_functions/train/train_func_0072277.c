_fetch(Evry_Plugin *plugin, const char *input)
{
   GET_PLUGIN(p, plugin);

   EVRY_PLUGIN_ITEMS_CLEAR(p);

   EVRY_PLUGIN_ITEMS_ADD(p, p->plugins, input, 1, 0);

   return EVRY_PLUGIN_HAS_ITEMS(p);
}
