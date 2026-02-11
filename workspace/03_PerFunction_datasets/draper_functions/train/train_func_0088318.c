remember_focus_widget (NemoWindowPane *pane)
{
	GtkWidget *focus_widget;

	focus_widget = gtk_window_get_focus (GTK_WINDOW (pane->window));
	if (focus_widget != NULL &&
	    !widget_is_in_temporary_bars (focus_widget, pane)) {
		unset_focus_widget (pane);

		pane->last_focus_widget = focus_widget;
		g_object_add_weak_pointer (G_OBJECT (focus_widget),
					   (gpointer *) &(pane->last_focus_widget));
	}
}
