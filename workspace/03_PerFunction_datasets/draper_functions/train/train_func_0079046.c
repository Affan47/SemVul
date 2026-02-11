wizard_response_cb (GtkDialog * dialog, int response, gpointer data)
{
	WizardWindow * wizard = (WizardWindow *)data;
	int current_page, num_pages;
	gboolean skip_mailbox_page = FALSE;
	gint protocol = combobox_get_active_data(GTK_COMBO_BOX(wizard->recv_type));

	if (protocol == A_IMAP4) {
		skip_mailbox_page = TRUE;
	}

	num_pages = g_slist_length(wizard->pages);

 	current_page = gtk_notebook_get_current_page (
				GTK_NOTEBOOK(wizard->notebook));
	if (response == CANCEL)
	{
		wizard->result = FALSE;
		wizard->finished = TRUE;
		gtk_widget_destroy (GTK_WIDGET(dialog));
	}
	else if (response == FINISHED)
	{
		if (!wizard_write_config(wizard)) {
 			current_page = gtk_notebook_get_current_page (
					GTK_NOTEBOOK(wizard->notebook));
			goto set_sens;
		}
		wizard->result = TRUE;
		wizard->finished = TRUE;
		gtk_widget_destroy (GTK_WIDGET(dialog));
	}
	else
	{
		if (response == GO_BACK)
		{
			if (current_page > 0) {
				current_page--;
				if (current_page == MAILBOX_PAGE && skip_mailbox_page) {

					current_page--;
				}
				gtk_notebook_set_current_page (
					GTK_NOTEBOOK(wizard->notebook),
					current_page);
			}
		}
		else if (response == GO_FORWARD)
		{
			if (current_page < (num_pages-1)) {
				current_page++;
				if (current_page == MAILBOX_PAGE && skip_mailbox_page) {

					current_page++;
				}
				gtk_notebook_set_current_page (
					GTK_NOTEBOOK(wizard->notebook),
					current_page);
			}
		}
set_sens:
		gtk_dialog_set_response_sensitive (dialog, GO_BACK,
				current_page > 0);
		gtk_dialog_set_response_sensitive (dialog, GO_FORWARD,
				current_page < (num_pages - 1));
		if (current_page == (num_pages -1)) {
			gtk_dialog_set_response_sensitive (dialog, FINISHED, TRUE);
			gtk_dialog_set_default_response(GTK_DIALOG(wizard->window), FINISHED);
		} else {
			gtk_dialog_set_response_sensitive (dialog, FINISHED, FALSE);
			gtk_dialog_set_default_response(GTK_DIALOG(wizard->window), GO_FORWARD);
		}

	}
}
