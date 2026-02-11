dw_summary_selected(GtkCMCTree *ctree, GtkCMCTreeNode *row,
			     gint column, day_win *dw)
{
	MsgInfo *msginfo = gtk_cmctree_node_get_row_data(ctree, row);
	int days = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dw->day_spin));

	if (msginfo && msginfo->msgid) {
		VCalEvent *event = vcal_manager_load_event(msginfo->msgid);
		if (event) {
			time_t t_first = mktime(&dw->startdate);
			time_t t_start = icaltime_as_timet(icaltime_from_string(event->dtstart));
			struct tm tm_start;
			gboolean changed = FALSE;
			GtkAdjustment *v_adj;

#ifdef G_OS_WIN32
			if (t_start < 0)
				t_start = 1;
#endif
			localtime_r(&t_start, &tm_start);
			tm_start.tm_hour = tm_start.tm_min = tm_start.tm_sec = 0;
			t_start = mktime(&tm_start);

			while (t_start < t_first) {
				changeSelectedDate(dw, -days);
				t_first = mktime(&dw->startdate);
				changed = TRUE;
			}
			while (t_start > t_first + (days-1)*24*60*60) {
				changeSelectedDate(dw, +days);
				t_first = mktime(&dw->startdate);
				changed = TRUE;
			}

			t_start = icaltime_as_timet(icaltime_from_string(event->dtstart));
#ifdef G_OS_WIN32
			if (t_start < 0)
				t_start = 1;
#endif
			localtime_r(&t_start, &tm_start);
			if (changed) {
				debug_print("changed from %s\n", event->summary);
				v_adj = gtk_scrolled_window_get_vadjustment(
				    GTK_SCROLLED_WINDOW(dw->scroll_win));
#ifdef G_OS_WIN32
				if (t_start < 0)
					t_start = 1;
#endif
				localtime_r(&t_start, &tm_start);
				if (tm_start.tm_hour > 2)
					gtk_adjustment_set_value(v_adj,
						(v_adj->upper-v_adj->page_size)/(24/(tm_start.tm_hour-2)));
				else
					gtk_adjustment_set_value(v_adj, 0);
				gtk_adjustment_changed(v_adj);
				refresh_day_win(dw);
			}
		}
		vcal_manager_free_event(event);
	}
}
