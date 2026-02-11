runModal(XAP_Frame * pFrame)
{
	m_pFrame = pFrame;


	GtkWidget * mainWindow = _constructWindow();
	UT_ASSERT(mainWindow);


	_populateWindowData();


	_connectCallbackSignals();


	gtk_widget_show(mainWindow);

#if defined(EMBEDDED_TARGET) && EMBEDDED_TARGET == EMBEDDED_TARGET_HILDON
#else

	{

		UT_ASSERT(m_drawingareaPreview && gtk_widget_get_window(m_drawingareaPreview));


		GR_UnixCairoAllocInfo ai(m_drawingareaPreview);
		m_unixGraphics =
		    (GR_CairoGraphics*) XAP_App::getApp()->newGraphics(ai);


		GtkAllocation allocation;
		gtk_widget_get_allocation(m_drawingareaPreview, &allocation);
		_createPreviewFromGC(m_unixGraphics,
							 (UT_uint32) allocation.width,
							 (UT_uint32) allocation.height);
	}


	_syncControls(id_MENU_ALIGNMENT, true);
#endif

	bool tabs;
	do {
		switch(abiRunModalDialog(GTK_DIALOG(mainWindow), pFrame, this, BUTTON_CANCEL, false))
		{
		case BUTTON_OK:
		  event_OK();
		  tabs = false;
		  break;
		case BUTTON_TABS:
		  event_Tabs ();
		  tabs = true;
		  break;
		default:
		  event_Cancel();
		  tabs = false;
		  break;
		}
	} while (tabs);

	abiDestroyWidget(mainWindow);
}
