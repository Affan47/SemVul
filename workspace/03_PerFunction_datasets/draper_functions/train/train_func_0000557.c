templates_load (AutoFormatState *state)
{
	GSList *l;
	gint n_templates;

	g_return_val_if_fail (state != NULL, FALSE);

	if (state->category_groups == NULL)
		return FALSE;

	state->templates = category_group_get_templates_list (
		state->current_category_group, GO_CMD_CONTEXT (state->wbcg));
	for (l = state->templates; l != NULL; l = l->next) {
		GnmFormatTemplate *ft = l->data;
		range_init (&ft->dimension,
			0, 0, PREVIEW_COLS - 1, PREVIEW_ROWS - 1);
		ft->invalidate_hash = TRUE;
	}
	n_templates = g_slist_length (state->templates);


	state->previews_locked = TRUE;
	{
		GtkAdjustment *adjustment = gtk_range_get_adjustment (GTK_RANGE (state->scroll));
		gtk_adjustment_configure (adjustment,
					  0, 0, n_templates / 2,
					  1, 3, 3);
	}
	state->previews_locked = FALSE;


	gtk_widget_set_visible (GTK_WIDGET (state->scroll),
				n_templates > NUM_PREVIEWS);

	return TRUE;
}
