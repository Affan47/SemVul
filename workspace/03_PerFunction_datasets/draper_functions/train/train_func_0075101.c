cb_update_to_new_range (SortFlowState *state)
{
        GnmValue *range;

        range = gnm_expr_entry_parse_as_value
		(GNM_EXPR_ENTRY (state->range_entry), state->sheet);
	if (range == NULL) {
		if (state->sel != NULL) {
			value_release (state->sel);
			state->sel = NULL;
			gtk_list_store_clear (state->model);
			state->sort_items = 0;
		}
	} else
		translate_range (range, state);
	set_button_sensitivity (state);
}
