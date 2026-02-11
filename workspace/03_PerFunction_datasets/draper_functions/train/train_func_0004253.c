prefs_matcher_set_dialog(MatcherList *matchers)
{
	GSList *cur;
	gboolean bool_op = 1;
	GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model
				(GTK_TREE_VIEW(matcher.cond_list_view)));

	gtk_list_store_clear(store);

	prefs_matcher_list_view_set_row(NULL, NULL);
	if (matchers != NULL) {
		for (cur = matchers->matchers; cur != NULL;
		     cur = g_slist_next(cur)) {
			MatcherProp *prop;
			prop = (MatcherProp *) cur->data;
			prefs_matcher_list_view_set_row(NULL, prop);
		}

		bool_op = matchers->bool_and;
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(matcher.bool_op_combo), bool_op);

	prefs_matcher_reset_condition();

	combobox_set_sensitive(GTK_COMBO_BOX(matcher.criteria_combo), MATCH_TAGS,
			(tags_get_size() > 0) ? TRUE : FALSE);
}
