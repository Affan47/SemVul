add_plugin_to_list(struct slapdplugin **list, struct slapdplugin *plugin)
{
	struct slapdplugin **tmp;
	struct slapdplugin *last = NULL;
	int plugin_added = 0;


	for ( tmp = list; *tmp; tmp = &(*tmp)->plg_next )
	{
		if (plugin->plg_precedence < (*tmp)->plg_precedence)
		{
			if (last)
			{

				plugin->plg_next = *tmp;
				last->plg_next = plugin;
			} else {

				plugin->plg_next = *tmp;
				*list = plugin;
			}

			plugin_added = 1;


			break;
		}


		last = *tmp;
	}


	if (!plugin_added)
	{
		*tmp = plugin;
	}
}
