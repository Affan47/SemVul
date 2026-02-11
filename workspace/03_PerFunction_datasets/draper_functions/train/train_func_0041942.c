on_idle_gtktextview_scroll_test (gpointer data)
{

	AppData *appdata = NULL;
	appdata = (AppData *) data;

	GtkRange *range;
	gdouble before, after;

	range = GTK_RANGE (GTK_SCROLLED_WINDOW
			   (appdata->scrolledwindow_text)->vscrollbar);

	before = gtk_range_get_value (range);
	g_signal_emit_by_name (range, "move-slider",
			       appdata->textview_text_scroll_type);
	after = gtk_range_get_value (range);


	if (before == after)
	{
		appdata->textview_text_scroll_type =
			(appdata->textview_text_scroll_type ==
			 GTK_SCROLL_STEP_FORWARD) ? GTK_SCROLL_STEP_BACKWARD :
			GTK_SCROLL_STEP_FORWARD;
	}


	toggle_test_count (appdata);

	return TRUE;
}
