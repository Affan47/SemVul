cb_tool_destroy (GenericToolState  *state)
{
	if (state->gui != NULL)
		g_object_unref (state->gui);
	wbcg_edit_finish (state->wbcg, WBC_EDIT_REJECT, NULL);
	if (state->state_destroy)
		state->state_destroy (state);
	g_free (state);
}
