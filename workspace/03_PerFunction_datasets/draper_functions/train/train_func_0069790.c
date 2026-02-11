file_eject_callback (NemoFile  *file,
		     GFile         *result_location,
		     GError        *error,
		     gpointer       callback_data)
{
	NemoView *view;

	view = NEMO_VIEW (callback_data);
	g_object_unref (view);

	if (error != NULL &&
	    (error->domain != G_IO_ERROR ||
	     (error->code != G_IO_ERROR_CANCELLED &&
	      error->code != G_IO_ERROR_FAILED_HANDLED))) {
		eel_show_error_dialog (_("Unable to eject location"),
				       error->message, NULL);
	}
}
