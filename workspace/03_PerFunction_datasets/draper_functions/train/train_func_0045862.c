toplevel_monitor_log_timer(gpointer data)
{
	toplevel_t *top = (toplevel_t *) data;
	if (top->do_monitor_log) {
		int retval;
		gint i = gtk_notebook_get_n_pages(top->notebook) - 1;
		uint delay;
		retval = seaudit_parse_log(top->s);
		if (retval < 0) {
			GtkCheckMenuItem *w;
			toplevel_ERR(top, "Error while monitoring log: %s", strerror(errno));
			w = GTK_CHECK_MENU_ITEM(glade_xml_get_widget(top->xml, "MonitorLog"));
			top->monitor_id = 0;
			gtk_check_menu_item_set_active(w, 0);
			return FALSE;
		}
		while (i >= 0) {
			GtkWidget *child = gtk_notebook_get_nth_page(top->notebook, i);
			GtkWidget *tab = gtk_notebook_get_tab_label(top->notebook, child);
			message_view_t *v = g_object_get_data(G_OBJECT(tab), "view-object");
			message_view_update_rows(v);
			i--;
		}


		delay = preferences_get_real_time_interval(toplevel_get_prefs(top));
		top->monitor_id = g_timeout_add(delay, toplevel_monitor_log_timer, top);
	} else {
		top->monitor_id = 0;
	}
	return FALSE;
}
