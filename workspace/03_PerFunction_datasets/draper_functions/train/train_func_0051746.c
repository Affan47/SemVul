brasero_caps_create_links (BraseroCaps *output,
	 		   GSList *inputs,
	 		   BraseroPlugin *plugin)
{
	for (; inputs; inputs = inputs->next) {
		BraseroCaps *input;
		BraseroCapsLink *link;

		input = inputs->data;

		if (output == input) {
			BRASERO_BURN_LOG ("Same input and output for link. Dropping");
			continue;
		}

		if (input->flags == output->flags
		&&  input->type.type == output->type.type
		&&  input->type.subtype.media == output->type.subtype.media)
			BRASERO_BURN_LOG ("Recursive link");

		link = brasero_caps_find_link_for_input (output, input);

#if 0


		BRASERO_BURN_LOG_TYPE (&output->type, "Linking");
		BRASERO_BURN_LOG_TYPE (&input->type, "to");
		BRASERO_BURN_LOG ("with %s", brasero_plugin_get_name (plugin));

#endif

		if (!link) {
			link = g_new0 (BraseroCapsLink, 1);
			link->caps = input;
			link->plugins = g_slist_prepend (NULL, plugin);

			output->links = g_slist_prepend (output->links, link);
		}
		else
			link->plugins = g_slist_prepend (link->plugins, plugin);
	}
}
