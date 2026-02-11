check_user_delete (OobsUser *user)
{
	GtkWidget *dialog;
	OobsGroupsConfig *config;
	OobsGroup *admin_group;
	GList *admin_users;
	gint response;

	config = OOBS_GROUPS_CONFIG (GST_USERS_TOOL (tool)->groups_config);
	admin_group = oobs_groups_config_get_from_name (config, ADMIN_GROUP);
	admin_users = oobs_group_get_users (admin_group);

	if (oobs_user_get_uid (user) == 0) {
		dialog = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
						 GTK_DIALOG_MODAL,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 _("Administrator account cannot be deleted"));

		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
							  _("This would leave the system unusable."));

	}
	else if (oobs_user_get_active (user)) {
		dialog = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
					 GTK_DIALOG_MODAL,
					 GTK_MESSAGE_INFO,
					 GTK_BUTTONS_CLOSE,
					 _("%s is currently using this computer"),
					 oobs_user_get_full_name_fallback (user));
		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
						  _("Please ensure the user has logged out before deleting this account."));
	}

	else if (oobs_user_is_in_group (user, admin_group)
	         && g_list_length (admin_users) < 2)
	{
		dialog = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
		                                 GTK_DIALOG_MODAL,
		                                 GTK_MESSAGE_ERROR,
		                                 GTK_BUTTONS_CLOSE,
		                                 _("Can't delete the only administrator account"));
		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
		                                          _("%s is the only administrator on this computer. "
		                                            "Deleting this account would lock you out of "
		                                            "administrating the system."),
		                                          oobs_user_get_full_name_fallback (user));
	}
	else {
		dialog = gtk_message_dialog_new (GTK_WINDOW (tool->main_dialog),
		                                 GTK_DIALOG_MODAL,
		                                 GTK_MESSAGE_QUESTION,
		                                 GTK_BUTTONS_NONE,
		                                 _("Remove home folder for %s?"),
		                                 oobs_user_get_full_name_fallback (user));
		gtk_message_dialog_format_secondary_markup (GTK_MESSAGE_DIALOG (dialog),
		                                            _("Files owned by user %s in <tt>%s</tt> can be completely "
		                                              "removed if you don't need them anymore. You may want to "
		                                              "back them up before deleting the account, or keep them "
		                                              "so that an administrator can save them later."),
		                                            oobs_user_get_login_name (user),
		                                            oobs_user_get_home_directory (user));

		gtk_dialog_add_buttons (GTK_DIALOG (dialog),
		                        _("Keep Files"), GTK_RESPONSE_NO,
		                        _("Don't Remove Account"), GTK_RESPONSE_CANCEL,
		                        _("Delete Files"), GTK_RESPONSE_YES,
		                        NULL);
		gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_CANCEL);
	}

	gst_dialog_add_edit_dialog (tool->main_dialog, dialog);
	response = gtk_dialog_run (GTK_DIALOG (dialog));
	gst_dialog_remove_edit_dialog (tool->main_dialog, dialog);

	gtk_widget_destroy (dialog);
	g_object_unref (admin_group);
	g_list_free (admin_users);


	if (response == GTK_RESPONSE_YES)
		oobs_user_set_home_flags (user, OOBS_USER_REMOVE_HOME);
	else
		oobs_user_set_home_flags (user, 0);

	return (response == GTK_RESPONSE_YES || response == GTK_RESPONSE_NO);
}
