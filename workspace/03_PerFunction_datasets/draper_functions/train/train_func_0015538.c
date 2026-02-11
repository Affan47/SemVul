file_stop_callback (NemoFile  *file,
		    GFile         *result_location,
		    GError        *error,
		    gpointer       callback_data)
{
	if (error != NULL &&
	    (error->domain != G_IO_ERROR ||
	     (error->code != G_IO_ERROR_CANCELLED &&
	      error->code != G_IO_ERROR_FAILED_HANDLED))) {
		eel_show_error_dialog (_("Unable to stop drive"),
				       error->message, NULL);
	}
}
