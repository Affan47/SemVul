s_pasteFile(const UT_UTF8String & file, XAP_Frame * pFrame)
{
	    if(!pFrame)
			return;
	    XAP_App * pApp = XAP_App::getApp();
	    PD_Document * newDoc = new PD_Document();
	    UT_Error err = newDoc->readFromFile(file.utf8_str(), IEFT_Unknown);
	    if ( err != UT_OK )
		{
			UNREFP(newDoc);
			return;
		}
		FV_View * pView = static_cast<FV_View *>(pFrame->getCurrentView());


		GR_Graphics *pGraphics = pView->getGraphics();

	    FL_DocLayout *pDocLayout = new FL_DocLayout(newDoc,pGraphics);
	    FV_View copyView(pApp,0,pDocLayout);

	    pDocLayout->setView (&copyView);
	    pDocLayout->fillLayouts();

	    copyView.cmdSelect(0, 0, FV_DOCPOS_BOD, FV_DOCPOS_EOD);
	    copyView.cmdCopy();
	    pView->cmdPaste ( true );

	    DELETEP(pDocLayout);
	    UNREFP(newDoc);
	    return ;
}
