policy_components_view_on_source_toggle(GtkToggleButton * widget, gpointer user_data)
{
	struct polcomp_view *pv = (struct polcomp_view *)user_data;


	if (!gtk_toggle_button_get_active(widget)) {
		return;
	}
	gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(pv->inc_store));
	gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(pv->exc_store));
}
