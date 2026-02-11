date_selection_set(GtkWidget *widget, gint day, gint month, gint year)
{
	DateSelection *ds;

	ds = g_object_get_data(G_OBJECT(widget), DATE_SELECION_KEY);
	if (!ds) return;

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(ds->spin_d), (gdouble)day);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(ds->spin_m), (gdouble)month);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(ds->spin_y), (gdouble)year);
}
