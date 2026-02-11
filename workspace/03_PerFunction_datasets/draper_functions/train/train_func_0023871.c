bl_doclistener_deleteCellStrux(fl_ContainerLayout* pBL, const PX_ChangeRecord_Strux * pcrx)
{
	bool bResult = true;
	UT_ASSERT(pBL->getContainerType() == FL_CONTAINER_CELL);
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	if(iCount <=0)
	{
		UT_ASSERT(0);
	}
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = m_vecPages.getNthItem(i);


		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		if(pShadowBL)
		{
			UT_ASSERT(pShadowBL->getContainerType() == FL_CONTAINER_CELL);
			bResult = static_cast<fl_CellLayout *>(pShadowBL)->doclistener_deleteStrux(pcrx)
				&& bResult;
		}
		else
		{
			UT_ASSERT(0);
		}
	}
	return bResult;
}
