loadDocument(AD_Document* pDoc) {
	bool bUpdateClones;
	UT_GenericVector<XAP_Frame*> vClones;
	XAP_App * pApp = XAP_App::getApp();
	UT_sint32 j = 0;
	if(pApp->findFrame(this) < 0)
	{
			pApp->rememberFrame(this);
	}
	bUpdateClones = (getViewNumber() > 0);
	if (bUpdateClones)
	{
		pApp->getClones(&vClones, this);
	}
	for(j=0; j<vClones.getItemCount();j++)
	{
		AP_Frame * pFrame = static_cast<AP_Frame *>(vClones.getNthItem(j));
		if(pApp->findFrame(pFrame) < 0)
		{
			pFrame->_replaceDocument(pDoc);
		}
	}

	return _replaceDocument(pDoc);
}
