onPrevClicked ()
{
	UT_DEBUGMSG (("ROB: onPrevClicked () '%d'\n", m_JumpTarget));

	UT_uint32 num = 0;
	switch (m_JumpTarget) {
		case AP_JUMPTARGET_PAGE:
			num = (UT_uint32)gtk_spin_button_get_value (GTK_SPIN_BUTTON (m_sbPage));
			if (num == 1)
				num = m_DocCount.page;
			else
				num--;
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_sbPage), num);
			break;
		case AP_JUMPTARGET_LINE:
			num = (UT_uint32)gtk_spin_button_get_value (GTK_SPIN_BUTTON (m_sbLine));
			if (num == 1)
				num = m_DocCount.line;
			else
				num--;
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (m_sbLine), num);
			break;
		case AP_JUMPTARGET_BOOKMARK:
			_selectPrevBookmark ();
			break;
		case AP_JUMPTARGET_XMLID:
            selectPrev(GTK_TREE_VIEW (m_lvXMLIDs));
			break;
		case AP_JUMPTARGET_ANNOTATION:
            selectPrev(GTK_TREE_VIEW (m_lvAnno));
			break;
		default:
			UT_DEBUGMSG (("ROB: AP_UnixDialog_Goto::onPrevClicked () no jump target\n"));
			return;

	}

	onJumpClicked ();
}
