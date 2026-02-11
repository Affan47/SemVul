gl_file_close (glWindow *window)
{
	glView  *view;
	glLabel *label;
	gboolean close = TRUE;

	gl_debug (DEBUG_FILE, "START");

	g_return_val_if_fail (window && GL_IS_WINDOW(window), TRUE);

	if ( !gl_window_is_empty (window) ) {

		view = GL_VIEW(window->view);
		label = view->label;

		if (gl_label_is_modified (label))	{
			GtkWidget *dialog;
			gchar *fname = NULL;
			gint ret;

			fname = gl_label_get_short_name (label);

			dialog = gtk_message_dialog_new (GTK_WINDOW(window),
							 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
							 GTK_MESSAGE_WARNING,
							 GTK_BUTTONS_NONE,
							 _("Save changes to document \"%s\" before closing?"),
							 fname);
			gtk_message_dialog_format_secondary_text (
				GTK_MESSAGE_DIALOG (dialog),
				_("Your changes will be lost if you don't save them."));

			gtk_dialog_add_button (GTK_DIALOG (dialog),
					       _("Close without saving"),
					       GTK_RESPONSE_NO);

			gtk_dialog_add_button (GTK_DIALOG (dialog),
					       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);

			gtk_dialog_add_button (GTK_DIALOG (dialog),
					       GTK_STOCK_SAVE, GTK_RESPONSE_YES);

			gtk_dialog_set_default_response	(GTK_DIALOG (dialog), GTK_RESPONSE_YES);

			gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);

			ret = gtk_dialog_run (GTK_DIALOG (dialog));

			gtk_widget_destroy (dialog);

			g_free (fname);

			switch (ret)
			{
			case GTK_RESPONSE_YES:
				close = gl_file_save (label, window);
				break;
			case GTK_RESPONSE_NO:
				close = TRUE;
				break;
			default:
				close = FALSE;
			}

			gl_debug (DEBUG_FILE, "CLOSE: %s", close ? "TRUE" : "FALSE");
		}

	}

	if (close) {
		gtk_widget_destroy (GTK_WIDGET(window));

		if ( gl_window_get_window_list () == NULL ) {

			gl_debug (DEBUG_FILE, "All windows closed.");

			gtk_main_quit ();
		}

	}

	gl_debug (DEBUG_FILE, "END");

	return close;
}
