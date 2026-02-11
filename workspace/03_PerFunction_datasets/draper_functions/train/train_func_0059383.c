gyrus_session_checkbutton_secure_toggled (GtkWidget *widget,
                                          gpointer data)
{
	g_return_if_fail (GTK_IS_SPIN_BUTTON (data));

	gtk_spin_button_set_value (GTK_SPIN_BUTTON (data),
			gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)) ?
				993 : 143);
}
