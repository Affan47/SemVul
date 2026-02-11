s_actuallyPrint(PD_Document *doc,  GR_Graphics *pGraphics,
		     FV_View * pPrintView, const char *pDocName,
		     UT_uint32 nCopies, bool bCollate,
		     UT_sint32 iWidth,  UT_sint32 iHeight,
		     const std::set<UT_sint32>& pages)
{
	UT_uint32 i,j,k;


	s_pLoadingDoc = static_cast<AD_Document *>(doc);

	if(pGraphics->startPrint())
	{
	  fp_PageSize ps = pPrintView->getPageSize();
	  bool orient = ps.isPortrait ();
	  pGraphics->setPortrait (orient);

	  const XAP_StringSet *pSS = XAP_App::getApp()->getStringSet ();
	  const gchar * msgTmpl = pSS->getValue (AP_STRING_ID_MSG_PrintStatus);

	  gchar msgBuf [1024];

	  dg_DrawArgs da;
	  memset(&da, 0, sizeof(da));
	  da.pG = pGraphics;

	  XAP_Frame * pFrame = XAP_App::getApp()->getLastFocussedFrame ();

		if (bCollate)
		{
			for (j=1; (j <= nCopies); j++)
				{
					i = 0;
					for (std::set<UT_sint32>::const_iterator page = pages.begin();
						 page != pages.end();
						 page++)
						{
							i++;
							k = *page;
							sprintf (msgBuf, msgTmpl, i, pages.size());

							if(pFrame) {
								pFrame->setStatusMessage ( msgBuf );
								pFrame->nullUpdate();
							}


							pGraphics->m_iRasterPosition = (k-1)*iHeight;
							pGraphics->startPage(pDocName, k, orient, iWidth, iHeight);
							pPrintView->draw(k-1, &da);
						}
				}
		}
		else
		{
			i = 0;
			for (std::set<UT_sint32>::const_iterator page = pages.begin();
				 page != pages.end();
				 page++)
				{
					k = *page;
					i++;

					for (j=1; (j <= nCopies); j++)
						{
							sprintf (msgBuf, msgTmpl, i, pages.size());

							if(pFrame) {
								pFrame->setStatusMessage ( msgBuf );
								pFrame->nullUpdate();
							}


							pGraphics->m_iRasterPosition = (k-1)*iHeight;
							pGraphics->startPage(pDocName, k, orient, iWidth, iHeight);
							pPrintView->draw(k-1, &da);
						}
				}
		}
		pGraphics->endPrint();

		if(pFrame)
		  pFrame->setStatusMessage ("");
	}
	s_pLoadingDoc = NULL;

	return true;
}
