runModal(XAP_Frame * pFrame)
{
	UT_return_if_fail(pFrame);


    m_window = _constructWindow();
    UT_return_if_fail(m_window);


	XAP_UnixApp * unixapp = static_cast<XAP_UnixApp *> (m_pApp);

	UT_return_if_fail(unixapp);
	UT_return_if_fail(m_previewArea && gtk_widget_get_window(m_previewArea));
	DELETEP (m_unixGraphics);


	GR_UnixCairoAllocInfo ai(m_previewArea);
	m_unixGraphics =
	    (GR_UnixCairoGraphics*) XAP_App::getApp()->newGraphics(ai);


	GtkAllocation allocation;
	gtk_widget_get_allocation(m_previewArea, &allocation);
	_createPreviewFromGC(m_unixGraphics,
		   static_cast<UT_uint32>(allocation.width),
		   static_cast<UT_uint32>(allocation.height));


	m_unixGraphics->init3dColors(m_previewArea);


	_updatePreview(m_recentAlign, m_recentControl);

	switch ( abiRunModalDialog ( GTK_DIALOG(m_window), pFrame, this,
								 CUSTOM_RESPONSE_INSERT, false ) )
	{
		case CUSTOM_RESPONSE_INSERT:
			m_answer = AP_Dialog_PageNumbers::a_OK;

			m_align   = m_recentAlign;
			m_control = m_recentControl;
			break;
		default:
			m_answer = AP_Dialog_PageNumbers::a_CANCEL;
			break;
	}

	DELETEP (m_unixGraphics);

	abiDestroyWidget ( m_window ) ;
}
