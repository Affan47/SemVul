update_public_sensitivity(GtkWidget *widget, gpointer data)
{
	char *service =
		gtk_combo_box_get_active_text(GTK_COMBO_BOX(chat_room_type));
	char *mservice = NULL;
	char *local_acc = NULL;
	int service_id = -1;
	int has_public = 0;

	if (!service && (!strstr(service, "]") || !strstr(service, " "))) {
		g_free(service);
		return;
	}

	local_acc = strstr(service, " ") + 1;
	*(strstr(service, "]")) = '\0';
	mservice = strstr(service, "[") + 1;

	service_id = get_service_id(mservice);
	g_free(service);

	has_public = (eb_services[service_id].sc->get_public_chatrooms != NULL);
	gtk_widget_set_sensitive(public_chkbtn, has_public);
	gtk_widget_set_sensitive(public_list_btn, has_public);
	if (has_public)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(public_chkbtn),
			FALSE);
}
