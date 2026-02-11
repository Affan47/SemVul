quote_colors_set_dialog_key_pressed(GtkWidget *widget,
						GdkEventKey *event,
						gpointer data)
{
	GtkColorSelectionDialog *dialog;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;

	dialog = GTK_COLOR_SELECTION_DIALOG(widget);
	g_object_get(dialog, "ok-button", &button_ok,
                         "cancel-button", &button_cancel,
                          NULL);

	if (event) {
		switch (event->keyval) {
			case GDK_KEY_Escape:
				gtk_button_clicked(GTK_BUTTON(&button_cancel));
				return TRUE;
			case GDK_KEY_Return:
			case GDK_KEY_KP_Enter:


				gtk_widget_grab_focus(button_ok);

				gtk_button_clicked(GTK_BUTTON(button_ok));
				return TRUE;
			default:
				break;
		}
	}
	return FALSE;
}
