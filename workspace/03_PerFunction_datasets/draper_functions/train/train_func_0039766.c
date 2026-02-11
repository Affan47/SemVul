gedit_document_saver_saving (GeditDocumentSaver *saver,
			     gboolean            completed,
			     GError             *error)
{


	if (completed)
	{
		g_object_ref (saver);
	}

	g_signal_emit (saver, signals[SAVING], 0, completed, error);

	if (completed)
	{
		if (error == NULL)
			gedit_debug_message (DEBUG_SAVER, "save completed");
		else
			gedit_debug_message (DEBUG_SAVER, "save failed");

		g_object_unref (saver);
	}
}
