addRevision(AD_Revision * pRev, bool bGenCR)
{
	m_vRevisions.addItem(pRev);
	if(bGenCR)
	{
		const gchar * szAtts[11]={"docprop","revision",
							 "revision",NULL,
							 "revision-desc",NULL,
							 "revision-time",NULL,
							 "revision-ver",NULL,NULL};
		UT_UTF8String sID,sTime,sVer;
		UT_UTF8String_sprintf(sID,"%d",pRev->getId());
		UT_UTF8String_sprintf(sTime,"%d",pRev->getStartTime());
		UT_UTF8String_sprintf(sVer,"%d",pRev->getVersion());
		UT_UTF8String sDesc(pRev->getDescription());
		szAtts[3]= sID.utf8_str();
		szAtts[5] = sDesc.utf8_str();
		szAtts[7] = sTime.utf8_str();
		szAtts[9] = sVer.utf8_str();
		createAndSendDocPropCR(szAtts,NULL);
	}
	forceDirty();
	return true;
}
