wbcg_validation_msg (WorkbookControl *wbc, ValidationStyle v,
		     char const *title, char const *msg)
{
	WBCGtk *wbcg = (WBCGtk *)wbc;
	ValidationStatus res0, res1 = GNM_VALIDATION_STATUS_VALID;
	char const *btn0, *btn1;
	GtkMessageType  type;
	GtkWidget  *dialog;
	int response;

	switch (v) {
	case GNM_VALIDATION_STYLE_STOP :
		res0 = GNM_VALIDATION_STATUS_INVALID_EDIT;		btn0 = _("_Re-Edit");
		res1 = GNM_VALIDATION_STATUS_INVALID_DISCARD;	btn1 = _("_Discard");
		type = GTK_MESSAGE_ERROR;
		break;
	case GNM_VALIDATION_STYLE_WARNING :
		res0 = GNM_VALIDATION_STATUS_VALID;			btn0 = _("_Accept");
		res1 = GNM_VALIDATION_STATUS_INVALID_DISCARD;	btn1 = _("_Discard");
		type = GTK_MESSAGE_WARNING;
		break;
	case GNM_VALIDATION_STYLE_INFO :
		res0 = GNM_VALIDATION_STATUS_VALID;			btn0 = GTK_STOCK_OK;
		btn1 = NULL;
		type = GTK_MESSAGE_INFO;
		break;
	case GNM_VALIDATION_STYLE_PARSE_ERROR:
		res0 = GNM_VALIDATION_STATUS_INVALID_EDIT;		btn0 = _("_Re-Edit");
		res1 = GNM_VALIDATION_STATUS_VALID;			btn1 = _("_Accept");
		type = GTK_MESSAGE_ERROR;
		break;

	default : g_return_val_if_fail (FALSE, 1);
	}

	dialog = gtk_message_dialog_new (wbcg_toplevel (wbcg),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		type, GTK_BUTTONS_NONE, "%s", msg);
	gtk_dialog_add_buttons (GTK_DIALOG (dialog),
		btn0, GTK_RESPONSE_YES,
		btn1, GTK_RESPONSE_NO,
		NULL);


	if (title)
		gtk_window_set_title (GTK_WINDOW (dialog), title);
	gtk_dialog_set_default_response (GTK_DIALOG (dialog), GTK_RESPONSE_NO);
	response = go_gtk_dialog_run (GTK_DIALOG (dialog),
				      wbcg_toplevel (wbcg));
	return ((response == GTK_RESPONSE_NO || response == GTK_RESPONSE_CANCEL) ? res1 : res0);
}
