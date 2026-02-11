cb_dialog_destroy (SortFlowState  *state)
{
	value_release (state->sel);
	state->sel = NULL;

	if (state->model != NULL)
		g_object_unref (state->model);
	if (state->gui != NULL)
		g_object_unref (state->gui);

	wbcg_edit_finish (state->wbcg, WBC_EDIT_REJECT, NULL);

	state->dialog = NULL;

	g_object_unref (state->image_ascending);
	state->image_ascending = NULL;
	g_object_unref (state->image_descending);
	state->image_descending = NULL;

	g_free (state);
}
