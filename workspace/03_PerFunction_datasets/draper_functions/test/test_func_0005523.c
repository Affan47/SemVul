s_doSpellDlg(FV_View * pView, XAP_Dialog_Id id)
{
   UT_return_val_if_fail(pView,false);
   XAP_Frame * pFrame = static_cast<XAP_Frame *> ( pView->getParentData());
   UT_return_val_if_fail(pFrame, false);

   pFrame->raise();

   XAP_DialogFactory * pDialogFactory
	 = static_cast<XAP_DialogFactory *>(pFrame->getDialogFactory());

   AP_Dialog_Spell * pDialog
	 = static_cast<AP_Dialog_Spell *>(pDialogFactory->requestDialog(id));
   UT_return_val_if_fail (pDialog, false);


   pDialog->runModal(pFrame);
   bool bOK = pDialog->isComplete();

   if (bOK)
	   s_TellSpellDone(pFrame, pDialog->isSelection());

   pDialogFactory->releaseDialog(pDialog);

   return bOK;
}
