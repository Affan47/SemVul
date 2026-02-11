isInBrokenTOC(fp_Container * pCon)
{


 	if(pCon->getMyBrokenContainer() == static_cast<fp_Container *>(this))
 	{
 		return true;
 	}
 	if(pCon->getMyBrokenContainer() != NULL)
 	{
 		return false;
 	}
	UT_sint32 iTop = 0;
	iTop = pCon->getY();
	UT_sint32 iHeight = pCon->getHeight();

	UT_sint32 iBot = iTop + iHeight;

	UT_sint32 iBreak = getYBreak();
	UT_sint32 iBottom = getYBottom();
	xxx_UT_DEBUGMSG(("Column %x iTop = %d ybreak %d iBot= %d ybottom= %d \n",getBrokenColumn(),iTop,iBreak,iBot,iBottom));
	if(iBot >= iBreak)
	{
		if(iBot < iBottom)
		{

			return true;
		}

	}
	return false;

}
