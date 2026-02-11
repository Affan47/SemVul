OnMaxChanged ()
{
	double min = gtk_spin_button_get_value (xminbtn);
	double max = gtk_spin_button_get_value (xmaxbtn);
	if (max <= min) {
		double step;
		gtk_spin_button_get_increments (xmaxbtn, &step, NULL);
		max = min + step;
		g_signal_handler_block (xmaxbtn, maxsgn);
		gtk_spin_button_set_value (xmaxbtn, max);
		g_signal_handler_unblock (xmaxbtn, maxsgn);
	}
	GogChart *chart = go_graph_widget_get_chart (GO_GRAPH_WIDGET (m_Widget));
	GSList *axes = gog_chart_get_axes (chart, GOG_AXIS_X);
	GogAxis *axis = GOG_AXIS (axes->data);
	gog_axis_set_bounds (axis, min, max);
	g_signal_handler_block (xrange, xrangesgn);
	if (max - min < xmax - xmin) {
		gtk_range_set_range (xrange, 0., xmax - xmin - max + min);
		gtk_range_set_value (xrange, min - xmin);
		gtk_widget_set_sensitive (GTK_WIDGET (xrange), true);
	} else {
		gtk_range_set_value (xrange, 0.);
		gtk_widget_set_sensitive (GTK_WIDGET (xrange), false);
	}
	g_signal_handler_unblock (xrange, xrangesgn);
}
