on_configure_response(GtkDialog *dialog, gint response, gpointer user_data)
{
	gboolean bSettingsChanged;
	GtkCheckButton *cb1,*cb2;

	if(response!=GTK_RESPONSE_OK && response!=GTK_RESPONSE_APPLY)
		return;


	cb1=(GtkCheckButton*)(g_object_get_data(G_OBJECT(dialog),"GeanyMacros_cb1"));
	cb2=(GtkCheckButton*)(g_object_get_data(G_OBJECT(dialog),"GeanyMacros_cb2"));


	bSettingsChanged=(bSaveMacros!=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb1)));
	bSettingsChanged|=(bQueryOverwriteMacros!=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb2)));


	bSaveMacros=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb1));
	bQueryOverwriteMacros=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb2));


	if(bSettingsChanged)
		SaveSettings();
}
