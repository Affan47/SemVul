set_adjustment_clamped (GtkAdjustment *adj, gdouble value)
{
	gdouble lower, upper, page_size;

	lower = gtk_adjustment_get_lower (adj);
	upper = gtk_adjustment_get_upper (adj);
	page_size = gtk_adjustment_get_page_size (adj);

	if (value < lower)
	{
		value = lower;
	}
	if (value > (upper - page_size))
	{
		value = upper - page_size;
	}
	gtk_adjustment_set_value (adj, value);
}
