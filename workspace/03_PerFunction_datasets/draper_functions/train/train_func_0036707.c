match_combo2_model_set(void)
{
	GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(matcher.match_combo2));
	if (model == matcher.model_age_units ||
	    model == matcher.model_found ||
	    model == matcher.model_partial ||
	    model == matcher.model_phrase ||
	    model == matcher.model_set ||
	    model == matcher.model_size_units ||
	    model == matcher.model_tags ||
	    model == matcher.model_thread)
		return TRUE;
	else
		debug_print("match_combo2 model unset.\n");

	return FALSE;
}
