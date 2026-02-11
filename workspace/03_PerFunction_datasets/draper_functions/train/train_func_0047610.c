plugin_opt_plugin (const char *plugin)
{
  plugin_t *newplug;

  newplug = xmalloc (sizeof *newplug);
  memset (newplug, 0, sizeof *newplug);
  newplug->name = plugin;
  newplug->dlhandle = dlopen (plugin, RTLD_NOW);
  if (!newplug->dlhandle)
    return set_plugin_error (plugin);


  *plugins_tail_chain_ptr = newplug;
  plugins_tail_chain_ptr = &newplug->next;


  last_plugin = newplug;
  last_plugin_args_tail_chain_ptr = &newplug->args;
  return 0;
}
