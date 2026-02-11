gtk_date_time_picker_set_datetime (GtkDateTimePicker* picker, GDateTime *datetime)
{
	g_return_if_fail(picker != NULL);
	g_return_if_fail(GTK_IS_DATE_TIME_PICKER(picker));
	g_return_if_fail(datetime != NULL);

	GtkDateTimePickerPrivate* priv;
	priv = GTK_DATE_TIME_PICKER_PRIVATE(picker);

	gchar* szTmp;

	szTmp = g_date_time_format (datetime, priv->szDateFormat);


	gtk_entry_set_text(GTK_ENTRY(priv->date_entry), szTmp);

	gtk_spin_button_set_value (GTK_SPIN_BUTTON(priv->hour_spinbutton),
	    g_date_time_get_hour (datetime));

	gtk_spin_button_set_value (GTK_SPIN_BUTTON(priv->minute_spinbutton),
	    g_date_time_get_minute (datetime));
}
