brasero_tool_dialog_response (GtkDialog *dialog,
			      GtkResponseType response,
			      gpointer NULL_data)
{
	if (response == GTK_RESPONSE_CANCEL) {
		if (!brasero_tool_dialog_cancel (BRASERO_TOOL_DIALOG (dialog)))
			g_signal_stop_emission_by_name (dialog, "response");
	}
	else if (response == GTK_RESPONSE_OK) {
		if (!brasero_tool_dialog_run (BRASERO_TOOL_DIALOG (dialog)))
			g_signal_stop_emission_by_name (dialog, "response");
	}
}
