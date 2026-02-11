editable_event_after_callback (GtkEntry *entry,
			       GdkEvent *event,
			       NemoLocationEntry *location_entry)
{
	GtkEditable *editable;
	GdkEventKey *keyevent;

	if (event->type != GDK_KEY_PRESS) {
		return;
	}

	editable = GTK_EDITABLE (entry);
	keyevent = (GdkEventKey *)event;


	if ((keyevent->keyval == GDK_KEY_Right || keyevent->keyval == GDK_KEY_End) &&
	    !(keyevent->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK)) &&
	    gtk_editable_get_selection_bounds (editable, NULL, NULL)) {
		set_position_and_selection_to_end (editable);
	}


	if (position_and_selection_are_at_end (editable)) {
		if (entry_would_have_inserted_characters (keyevent)) {
			if (location_entry->details->idle_id == 0) {
				location_entry->details->idle_id = g_idle_add (try_to_expand_path, location_entry);
			}
		}
	} else {


		if (location_entry->details->idle_id != 0) {
			g_source_remove (location_entry->details->idle_id);
			location_entry->details->idle_id = 0;
		}
	}
}
