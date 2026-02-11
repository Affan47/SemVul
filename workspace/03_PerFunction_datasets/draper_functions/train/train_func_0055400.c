gtk_knob_button_release(GtkWidget *widget, GdkEventButton *event) {
    GtkKnob *knob;

    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (GTK_IS_KNOB (widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);
    g_return_val_if_fail (GTK_IS_ADJUSTMENT (GTK_KNOB (widget)->adjustment), FALSE);

    knob = GTK_KNOB (widget);

    switch (knob->state) {

    case STATE_PRESSED:
	knob->state = STATE_IDLE;
	break;

    case STATE_DRAGGING:
	knob->state = STATE_IDLE;

	switch (event->button) {
	case 1:
	case 3:
	    if (knob->policy != GTK_KNOB_UPDATE_CONTINUOUS
		&& knob->old_value != gtk_adjustment_get_value(knob->adjustment))
	    {
		g_signal_emit_by_name (knob->adjustment, "value_changed");
	    }
	    break;
	}

	break;
    }

    return FALSE;
}
