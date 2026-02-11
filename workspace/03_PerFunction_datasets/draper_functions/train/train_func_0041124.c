glade_gtk_spin_button_set_adjustment (GObject *object, const GValue *value)
{
	GObject *adjustment;
	GtkAdjustment *adj;

	g_return_if_fail (GTK_IS_SPIN_BUTTON (object));

	adjustment = g_value_get_object (value);

	if (adjustment && GTK_IS_ADJUSTMENT (adjustment))
	{
		adj = GTK_ADJUSTMENT (adjustment);

		if (gtk_adjustment_get_page_size (adj) > 0)
		{
			GladeWidget *gadj = glade_widget_get_from_gobject (adj);


			if (gadj)

				glade_widget_property_set (gadj, "page-size", 0.0F);

			gtk_adjustment_set_page_size (adj, 0);
		}

		gtk_spin_button_set_adjustment (GTK_SPIN_BUTTON (object), adj);
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (object),
					   gtk_adjustment_get_value (adj));
	}
}
