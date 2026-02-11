s_AskRevertFile(XAP_Frame * pFrame)
{


	char *pFilename = UT_go_filename_from_uri(pFrame->getFilename());

	bool b = (pFrame->showMessageBox(AP_STRING_ID_MSG_RevertBuffer,
										XAP_Dialog_MessageBox::b_YN,
										XAP_Dialog_MessageBox::a_YES,
										pFilename)
						== XAP_Dialog_MessageBox::a_YES);

	FREEP(pFilename);
	return b;
}
