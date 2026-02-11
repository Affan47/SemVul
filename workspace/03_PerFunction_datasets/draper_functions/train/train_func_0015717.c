odf_config_stack_pop (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	OOParseState *state = (OOParseState *)xin->user_state;

	g_return_if_fail (state->settings.stack != NULL);

	g_hash_table_unref (state->settings.stack->data);
	state->settings.stack = g_slist_delete_link
		(state->settings.stack, state->settings.stack);
}
