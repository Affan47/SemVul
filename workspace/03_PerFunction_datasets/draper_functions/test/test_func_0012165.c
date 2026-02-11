gtk_dateentry_set_mindate(GtkDateEntry *dateentry, guint32 julian_days)
{
	DB( g_print(" \n[dateentry] set date\n") );

	g_return_if_fail (GTK_IS_DATE_ENTRY (dateentry));

	if(g_date_valid_julian(julian_days))
	{
		g_date_set_julian (&dateentry->mindate, julian_days);
	}
}
