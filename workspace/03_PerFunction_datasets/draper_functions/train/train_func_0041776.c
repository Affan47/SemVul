_e2_fileview_column_header_buttonrel_cb
	(GtkWidget *header, GdkEventButton *event, ViewInfo *view)
{
	printd (DEBUG, "callback: column header button release");

	if (view != curr_view)
		e2_pane_activate_other ();


	gboolean pressed = FALSE;
	if (!block && event->send_event)
	{
		pressed = TRUE;
		block = TRUE;
	}
	else if (block)
		block = FALSE;


	if (!pressed)
		header_button = -1;
	return pressed;
}
