named_spin_set_limits(GtkWidget *dialog, char *name, double min, double max)
{
	GtkWidget *spin;
	GtkAdjustment *adj;
	g_return_if_fail(dialog != NULL);
	spin = gtk_object_get_data(GTK_OBJECT(dialog), name);
	g_return_if_fail(spin != NULL);
	adj = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(spin));
	g_return_if_fail(adj != NULL);
	adj->lower = min;
	adj->upper = max;
	gtk_adjustment_changed(GTK_ADJUSTMENT(adj));
}
