cb_timer_enable(GtkWidget *button, gpointer data)
	{
	gkrellm_panel_enable_visibility(timer_panel,
				GTK_TOGGLE_BUTTON(enable_net_timer_button)->active,
				&timer_button_enabled);
	gtk_widget_set_sensitive(net_timer_seconds_button, timer_button_enabled);
	if (timer_iface_combo_box)
		{

		if (!timer_button_enabled)
			gtk_combo_box_set_active(GTK_COMBO_BOX(timer_iface_combo_box), 0);
		gtk_widget_set_sensitive(timer_iface_combo_box, timer_button_enabled);
		}
	net_timer_visibility();
	}
