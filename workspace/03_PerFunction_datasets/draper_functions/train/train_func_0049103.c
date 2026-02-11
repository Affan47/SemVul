plugin_call_all_symbols_read (void)
{
  plugin_t *curplug = plugins_list;


  no_more_claiming = TRUE;

  while (curplug)
    {
      if (curplug->all_symbols_read_handler)
	{
	  enum ld_plugin_status rv;
	  called_plugin = curplug;
	  rv = (*curplug->all_symbols_read_handler) ();
	  called_plugin = NULL;
	  if (rv != LDPS_OK)
	    set_plugin_error (curplug->name);
	}
      curplug = curplug->next;
    }
  return plugin_error_p () ? -1 : 0;
}
