show_prediction(ScintillaObject* scintilla, presage_t presage)
{
    char** prediction;
    char* list;
    presage_error_code_t result;

    result = presage_predict(presage, &prediction);
    if (PRESAGE_OK == result)
    {
	list = stringify_prediction (prediction);
	presage_free_string_array (prediction);

	g_print ("prediction: %s|\n", list);

	uptr_t completion_active;

	completion_active = scintilla_send_message (scintilla,
						    SCI_AUTOCACTIVE,
						    0,
						    0);

	if (completion_active)
	{
	    scintilla_send_message (scintilla,
				    SCI_AUTOCCANCEL,
				    0,
				    0);
	}

	scintilla_send_message (scintilla,
				SCI_USERLISTSHOW,
				1,
				(sptr_t) list);

	free (list);

    } else if (PRESAGE_SQLITE_EXECUTE_SQL_ERROR == result) {

	if (PRESAGE_OK == presage_config_set (presage,
					      "Presage.Predictors.SmoothedNgramPredictor.LEARN",
					      "false"))
	{

	    GtkWidget* dialog = gtk_message_dialog_new (NULL,
							GTK_DIALOG_DESTROY_WITH_PARENT,
							GTK_MESSAGE_ERROR,
							GTK_BUTTONS_CLOSE,
							"The adaptive text learning component of the presage predictive text entry engine has detected an error. Learning has been switched off.");
	    gtk_dialog_run (GTK_DIALOG (dialog));
	    gtk_widget_destroy (dialog);
        }
    }


}
