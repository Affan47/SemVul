runModal (XAP_Frame * pFrame)
{
	if (pFrame == NULL) return;


	GtkWidget * mainWindow = _constructWindow ();

	if (mainWindow == NULL) return;

	bool stop = false;
	while (!stop)
		switch (abiRunModalDialog (GTK_DIALOG (mainWindow), pFrame, this, BUTTON_OK, false))
			{
			case BUTTON_OK:
				event_OK ();
				stop = true;
				break;
			case BUTTON_SAVE_SETTINGS:
				event_SaveSettings ();
				break;
			case BUTTON_RESTORE_SETTINGS:
				event_RestoreSettings ();
				break;
			case BUTTON_CANCEL:
			default:
				event_Cancel ();
				stop = true;
				break;
			}
	abiDestroyWidget (mainWindow);
}
