_e2_size_filter_dialog_ok (E2_SzFltDlgData *rt)
{
	gint index = gtk_combo_box_get_active (GTK_COMBO_BOX (rt->operation_combo));
	rt->view->size_filter.op = index;

	const gchar *s = gtk_entry_get_text (GTK_ENTRY (rt->size_entry));
	gdouble dsize = atof (s);
	index = gtk_combo_box_get_active (GTK_COMBO_BOX (rt->units_combo));
	if (index == 1 || index == 2)
	  dsize *= pow (1024, index);
	rt->view->size_filter.size = (size_t)dsize;
	rt->view->size_filter.active = TRUE;

	e2_toolbar_toggle_filter_button (rt->view);
	e2_fileview_refilter_list (rt->view);
#ifdef E2_STATUS_DEMAND
	if (rt->view == curr_view)
	  e2_window_update_status_bar (NULL);
#endif
}
