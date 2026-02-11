_e2p_find_get_datetime (time_t *choice, spinners *times)
{
	gboolean retval;
	GDate *target = g_date_new ();
	g_date_set_dmy (target,
	gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (times->day_spin)),
	gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (times->month_spin)),
	gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (times->year_spin)) );

	if (g_date_valid (target))
	{
		struct tm tm;
		g_date_to_struct_tm (target, &tm);
     	tm.tm_hour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (times->hour_spin));
     	tm.tm_min = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (times->minute_spin));
		tm.tm_sec = 0;
		*choice = mktime (&tm);
		retval = TRUE;
	}
	else
	{
		*choice = 0;
		retval = FALSE;
	}
	g_date_free (target);
	return retval;
}
