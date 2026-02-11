runModal(XAP_Frame * pFrame)
{
	UT_return_if_fail(pFrame);


	m_windowMain = _constructWindow();
	UT_return_if_fail(m_windowMain);

	switch(abiRunModalDialog(GTK_DIALOG(m_windowMain), pFrame, this,
							 GTK_RESPONSE_OK, true ))
	{
		case GTK_RESPONSE_OK:
			setAnswer(a_OK);
			break;
		default:
			setAnswer(a_CANCEL);
			break;
	}
}
