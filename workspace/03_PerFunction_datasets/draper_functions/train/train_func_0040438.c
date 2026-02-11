cb_category_changed (AutoFormatState *state)
{
	GList *selection = g_list_nth (state->category_groups,
		gtk_combo_box_get_active (state->category));
	char const *tip = NULL;

	state->current_category_group = (selection != NULL) ? selection->data : NULL;
	previews_free (state);
	templates_free (state);
	if (templates_load (state) == FALSE)
		g_warning ("Error while loading templates!");

	if (NULL != state->current_category_group) {
		tip = state->current_category_group->description;
		if (NULL == tip)
			tip = state->current_category_group->name;
	}
	gtk_widget_set_tooltip_text (GTK_WIDGET (state->category),
		(NULL != tip) ? _(tip) : "");
	previews_load (state, 0);
	cb_check_item_toggled (NULL, state);
	cb_canvas_button_press (state->canvas[0], NULL, state);
}
