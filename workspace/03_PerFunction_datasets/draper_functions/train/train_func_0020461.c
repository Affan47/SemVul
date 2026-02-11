findToolbarNr(EV_Toolbar * pTB)
{
	UT_sint32 i = 0;
	bool bFound =  false;
	for(i =0; !bFound && (i < m_pFrameImpl->m_vecToolbars.getItemCount()); i++)
	{
		EV_Toolbar * pTmp = getToolbar(i);
		if(pTmp == pTB)
		{
			bFound  = true;
			break;
		}
	}
	if(bFound)
	{
		return static_cast<UT_sint32>(i);
	}
	return -1;
}
