atp_on_variable_dialog_response (GtkDialog *dialog, gint response, gpointer user_data)
{
	ATPVariableDialog *this = (ATPVariableDialog *)user_data;
	gchar* name;

	switch (response)
	{
	case GTK_RESPONSE_OK:
		name = get_current_name (this->view);
		atp_variable_dialog_add_variable (this, name);
		break;
	default:
		break;
	}

	gtk_widget_hide (GTK_WIDGET (this->dialog));
}
