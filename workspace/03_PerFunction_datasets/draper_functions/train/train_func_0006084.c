s_doInsertTableDlg(FV_View * pView)
{
	UT_return_val_if_fail(pView, false);
	XAP_Frame * pFrame = static_cast<XAP_Frame *> ( pView->getParentData());
	UT_return_val_if_fail(pFrame, false);

	pFrame->raise();

	XAP_DialogFactory * pDialogFactory
		= static_cast<XAP_DialogFactory *>(pFrame->getDialogFactory());

	AP_Dialog_InsertTable * pDialog
		= static_cast<AP_Dialog_InsertTable *>(pDialogFactory->requestDialog(AP_DIALOG_ID_INSERT_TABLE));
UT_return_val_if_fail(pDialog, false);
	pDialog->runModal(pFrame);

	AP_Dialog_InsertTable::tAnswer ans = pDialog->getAnswer();
	bool bOK = (ans == AP_Dialog_InsertTable::a_OK);


	if (bOK)
	{
		if (pDialog->getColumnType() == AP_Dialog_InsertTable::b_FIXEDSIZE)
		{
			UT_String tmp;
			UT_String propBuffer;
			UT_LocaleTransactor t(LC_NUMERIC, "C");
			for (UT_uint32 i = 0; i<pDialog->getNumCols(); i++)
			{
				UT_String_sprintf(tmp, "%fin/", pDialog->getColumnWidth());
				propBuffer += tmp;
			}
			const gchar * propsArray[3];
			propsArray[0] = "table-column-props";
			propsArray[1] = propBuffer.c_str();
			propsArray[2] = NULL;
			pView->cmdInsertTable(pDialog->getNumRows(),pDialog->getNumCols(),propsArray);
		} else
		{
			pView->cmdInsertTable(pDialog->getNumRows(),pDialog->getNumCols(),NULL);
		}
	}

	pDialogFactory->releaseDialog(pDialog);

	return bOK;
}
