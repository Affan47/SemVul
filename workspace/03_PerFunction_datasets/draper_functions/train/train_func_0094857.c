build_tools_preferences_on_view_selection_changed (BuildToolsPreferences* self, GtkTreeSelection* select, GtkTreeSelection* other_select) {
	GList* selected_items = NULL;
	GtkTreeSelection* _tmp0_ = NULL;
	GList* _tmp1_ = NULL;
	GList* _tmp2_ = NULL;
	guint _tmp3_ = 0U;
	g_return_if_fail (self != NULL);
	g_return_if_fail (select != NULL);
	g_return_if_fail (other_select != NULL);
	_tmp0_ = select;
	_tmp1_ = gtk_tree_selection_get_selected_rows (_tmp0_, NULL);
	selected_items = _tmp1_;
	_tmp2_ = selected_items;
	_tmp3_ = g_list_length (_tmp2_);
	if (_tmp3_ > ((guint) 0)) {
		GtkTreeSelection* _tmp4_ = NULL;
		_tmp4_ = other_select;
		gtk_tree_selection_unselect_all (_tmp4_);
	}
	__g_list_free__gtk_tree_path_free0_0 (selected_items);
}
