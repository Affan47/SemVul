ui_table_add_row(GtkTable *table, gint row, ...)
{
	va_list args;
	guint i;
	GtkWidget *widget;

	va_start(args, row);
	for (i = 0; (widget = va_arg(args, GtkWidget*), widget != NULL); i++)
	{
		gint options = (i == 0) ? GTK_FILL : GTK_EXPAND | GTK_FILL;

		gtk_table_attach(GTK_TABLE(table), widget, i, i + 1, row, row + 1,
			options, 0, 0, 0);
	}
	va_end(args);
}
