scroll_postpone(gpointer data)
{
	Compose *compose = (Compose *)data;

	cm_return_val_if_fail(!compose->batch, FALSE);

	GTK_EVENTS_FLUSH();
	compose_show_first_last_header(compose, FALSE);
	return FALSE;
}
