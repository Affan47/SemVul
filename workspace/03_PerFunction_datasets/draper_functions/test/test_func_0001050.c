gtk_knob_adjustment_changed(GtkAdjustment *adjustment, gpointer data) {
    GtkKnob *knob;

    g_return_if_fail (adjustment != NULL);
    g_return_if_fail (data != NULL);

    knob = GTK_KNOB (data);

    if ((knob->old_value != gtk_adjustment_get_value(adjustment)) ||
	(knob->old_lower != gtk_adjustment_get_lower(adjustment)) ||
	(knob->old_upper != gtk_adjustment_get_upper(adjustment)))
    {
	gtk_knob_update (knob);

	knob->old_value = gtk_adjustment_get_value(adjustment);
	knob->old_lower = gtk_adjustment_get_lower(adjustment);
	knob->old_upper = gtk_adjustment_get_upper(adjustment);
    }
}
