gtk_knob_adjustment_changed(GtkAdjustment *adjustment, gpointer data)
{
    GtkKnob *knob;

    g_return_if_fail(adjustment != NULL);
    g_return_if_fail(data != NULL);

    knob = GTK_KNOB(data);

    knob->old_value = adjustment->value;

    gtk_widget_queue_draw (GTK_WIDGET(knob));
}
