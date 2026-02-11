more_parts (GtkWidget *button,
            FilterRuleData *data)
{
	EFilterPart *new;


	if (data->rule->parts) {
		EFilterPart *part;
		GList *l;
		EAlert *alert = NULL;

		l = g_list_last (data->rule->parts);
		part = l->data;
		if (!e_filter_part_validate (part, &alert)) {
			GtkWidget *toplevel;
			toplevel = gtk_widget_get_toplevel (button);
			e_alert_run_dialog (GTK_WINDOW (toplevel), alert);
			return;
		}
	}


	new = e_rule_context_next_part (data->context, NULL);
	if (new) {
		GtkWidget *w;
		guint rows;

		new = e_filter_part_clone (new);
		e_filter_rule_add_part (data->rule, new);
		w = get_rule_part_widget (data->context, new, data->rule);

		g_object_get (data->parts, "n-rows", &rows, NULL);
		gtk_table_resize (GTK_TABLE (data->parts), rows + 1, 2);
		attach_rule (w, data, new, rows);

		if (GTK_IS_CONTAINER (w)) {
			gboolean done = FALSE;

			gtk_container_foreach (GTK_CONTAINER (w), do_grab_focus_cb, &done);
		} else
			gtk_widget_grab_focus (w);


		w = (GtkWidget *) g_object_get_data (G_OBJECT (button), "scrolled-window");
		if (w) {
			GtkAdjustment *adjustment;

			adjustment = gtk_scrolled_window_get_vadjustment (
				GTK_SCROLLED_WINDOW (w));
			if (adjustment) {
				gdouble upper;

				upper = gtk_adjustment_get_upper (adjustment);
				gtk_adjustment_set_value (adjustment, upper);
			}

		}
	}
}
