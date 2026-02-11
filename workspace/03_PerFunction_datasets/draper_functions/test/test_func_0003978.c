e_cell_combo_button_release (GtkWidget *popup_window,
                             GdkEvent *button_event,
                             ECellCombo *ecc)
{
	GtkWidget *event_widget;
	guint32 event_time;

	event_time = gdk_event_get_time (button_event);
	event_widget = gtk_get_event_widget (button_event);


	while (event_widget && event_widget != ecc->popup_tree_view)
		event_widget = gtk_widget_get_parent (event_widget);


	if (event_widget != ecc->popup_tree_view)
		return FALSE;


	gtk_grab_remove (ecc->popup_window);

	if (ecc->grabbed_keyboard != NULL) {
		gdk_device_ungrab (ecc->grabbed_keyboard, event_time);
		g_object_unref (ecc->grabbed_keyboard);
		ecc->grabbed_keyboard = NULL;
	}

	if (ecc->grabbed_pointer != NULL) {
		gdk_device_ungrab (ecc->grabbed_pointer, event_time);
		g_object_unref (ecc->grabbed_pointer);
		ecc->grabbed_pointer = NULL;
	}

	gtk_widget_hide (ecc->popup_window);

	e_cell_popup_set_shown (E_CELL_POPUP (ecc), FALSE);
	d (g_print ("%s: popup_shown = FALSE\n", __FUNCTION__));

	e_cell_combo_update_cell (ecc);
	e_cell_combo_restart_edit (ecc);

	return TRUE;
}
