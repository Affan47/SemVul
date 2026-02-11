start_element (GMarkupParseContext *context,
                           const gchar         *element_name,
			   const gchar        **attribute_names,
			   const gchar        **attribute_values,
			   gpointer             user_data,
			   GError             **error)
{
	ParseState *state = user_data;
	if (!state->current) {
		state->current = g_hash_table_lookup (config_handlers, element_name);
		if (state->current && state->current->init)
			state->user_data = state->current->init (state->assembly);
	}
	if (state->current && state->current->start)
		state->current->start (state->user_data, element_name, attribute_names, attribute_values);
}
