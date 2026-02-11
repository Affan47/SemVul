date_selection_time_set(GtkWidget *widget, time_t t)
{
	struct tm *lt;

	lt = localtime(&t);
	if (!lt) return;

	date_selection_set(widget, lt->tm_mday, lt->tm_mon + 1, lt->tm_year + 1900);
}
