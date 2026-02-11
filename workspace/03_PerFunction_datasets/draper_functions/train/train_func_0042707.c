event_ModifyClicked(void)
{
	PD_Style * pStyle = NULL;
	const char * szCurrentStyle = getCurrentStyle ();
	m_sNewStyleName = szCurrentStyle;

	if(szCurrentStyle)
		getDoc()->getStyle(szCurrentStyle, &pStyle);

	if (!pStyle)
	{

		return;
	}


#if 0
	if (!pStyle->isUserDefined ())
	{

		const XAP_StringSet * pSS = m_pApp->getStringSet();
		std::string s;
		pSS->getValueUTF8 (AP_STRING_ID_DLG_Styles_ErrStyleBuiltin,s);
		const gchar * msg = s.c_str();

		getFrame()->showMessageBox (static_cast<const char *>(msg),
									XAP_Dialog_MessageBox::b_O,
									XAP_Dialog_MessageBox::a_OK);
		return;
	}
#endif

#if HIDE_MAIN_DIALOG


    gtk_widget_hide(m_windowMain);
#endif


	setIsNew(false);

	modifyRunModal();
	if(m_answer == AP_Dialog_Styles::a_OK)
	{
		applyModifiedStyleToDoc();
		getDoc()->updateDocForStyleChange(getCurrentStyle(),true);
		getDoc()->signalListeners(PD_SIGNAL_UPDATE_LAYOUT);
	}
	else
	{


	}


#if HIDE_MAIN_DIALOG


	gtk_widget_show( m_windowMain);
#endif
}
