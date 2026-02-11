cb_handlebox_button_press (GtkHandleBox *hdlbox, GdkEventButton *event, WBCGtk *gtk)
{
	if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
		GtkToolbar *tb = GTK_TOOLBAR (gtk_bin_get_child (GTK_BIN (hdlbox)));
		toolbar_context_menu (tb, gtk, event);
		return TRUE;
	}

	return FALSE;
}
