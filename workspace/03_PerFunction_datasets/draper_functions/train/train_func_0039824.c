connect_dialog_finish_fill (NemoConnectServerDialog *dialog)
{
	GAskPasswordFlags flags;
	GMountOperation *op;

	flags = dialog->details->fill_details_flags;
	op = G_MOUNT_OPERATION (dialog->details->fill_operation);

	if (flags & G_ASK_PASSWORD_NEED_PASSWORD) {
		g_mount_operation_set_password (op, gtk_entry_get_text (GTK_ENTRY (dialog->details->password_entry)));
	}

	if (flags & G_ASK_PASSWORD_NEED_USERNAME) {
		g_mount_operation_set_username (op, gtk_entry_get_text (GTK_ENTRY (dialog->details->user_entry)));
	}

	if (flags & G_ASK_PASSWORD_NEED_DOMAIN) {
		g_mount_operation_set_domain (op, gtk_entry_get_text (GTK_ENTRY (dialog->details->domain_entry)));
	}

	if (flags & G_ASK_PASSWORD_SAVING_SUPPORTED &&
	    gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (dialog->details->remember_checkbox))) {
		g_mount_operation_set_password_save (op, G_PASSWORD_SAVE_PERMANENTLY);
	}

	connect_dialog_set_connecting (dialog);

	g_simple_async_result_set_op_res_gboolean (dialog->details->fill_details_res, TRUE);
	g_simple_async_result_complete (dialog->details->fill_details_res);

	g_object_unref (dialog->details->fill_details_res);
	dialog->details->fill_details_res = NULL;

	g_object_unref (dialog->details->fill_operation);
	dialog->details->fill_operation = NULL;
}
