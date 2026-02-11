middle_finish(void)
{
	eb_debug(DBG_MOD, "L33tSp33k shutting down\n");
	outgoing_message_filters_local =
		l_list_remove(outgoing_message_filters_local, &plstripHTML);
	outgoing_message_filters_remote =
		l_list_remove(outgoing_message_filters_remote, &plstripHTML);
	incoming_message_filters =
		l_list_remove(incoming_message_filters, &plstripHTML);

	while (plugin_info.prefs) {
		input_list *il = plugin_info.prefs->next;
		free(plugin_info.prefs);
		plugin_info.prefs = il;
	}

	return (0);
}
