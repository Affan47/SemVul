event_OK(void)
{
	UT_ASSERT(m_window);


    std::string mark = tostr(GTK_ENTRY(m_combo));
	if( !mark.empty() )
	{
		xxx_UT_DEBUGMSG(("InsertXMLID: OK pressed, first char 0x%x\n", (UT_uint32)mark[0]));
		setAnswer(AP_Dialog_InsertXMLID::a_OK);
		setString(mark);
	}
	else
	{
		setAnswer(AP_Dialog_InsertXMLID::a_CANCEL);
	}
}
