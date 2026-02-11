runModal(XAP_Frame * pFrame)
{
	GtkWidget * mainWindow = constructWindow();
	UT_return_if_fail(mainWindow);


	event_FocusToggled () ;

    gint rc = abiRunModalDialog ( GTK_DIALOG(mainWindow),
                                  pFrame, this, BUTTON_CANCEL, false );
    UT_DEBUGMSG(("AP_UnixDialog_MarkRevisions::runModal() rc:%d\n", rc ));

	switch ( rc )
	{
		case BUTTON_OK:
			event_OK () ; break ;
		default:
			event_Cancel () ; break ;
	}


	abiDestroyWidget ( mainWindow ) ;
}
