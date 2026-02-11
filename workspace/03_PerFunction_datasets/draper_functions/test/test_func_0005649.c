panel_applet_button_press (GtkWidget      *widget,
			   GdkEventButton *event)
{
	PanelApplet *applet = PANEL_APPLET (widget);

	if (!container_has_focusable_child (GTK_CONTAINER (applet))) {
		if (!gtk_widget_has_focus (widget)) {
			gtk_widget_set_can_focus (widget, TRUE);
			gtk_widget_grab_focus (widget);
		}
	}

	if (event->button == 3) {
		guint modifiers;

		modifiers = event->state & gtk_accelerator_get_default_mod_mask ();

		if (modifiers == panel_applet_bindings_get_mouse_button_modifier_keymask ())
			panel_applet_edit_menu_popup (applet, event->button, event->time);
		else
			panel_applet_menu_popup (applet, event->button, event->time);

		return TRUE;
	}

	return panel_applet_button_event (applet->priv->plug, event);
}
