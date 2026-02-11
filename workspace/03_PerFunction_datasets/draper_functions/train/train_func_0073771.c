_drawCellProperties(const AP_LeftRulerInfo * pInfo)
{
	if(pInfo->m_mode != AP_LeftRulerInfo::TRI_MODE_TABLE)
	{
		return;
	}
	if(m_pG == NULL)
	{
		return;
	}
	UT_sint32 nrows = pInfo->m_iNumRows;
	UT_sint32 i = 0;
	UT_Rect rCell;
	xxx_UT_DEBUGMSG(("ap_LeftRuler: Draw Cell Marks start \n"));
	fp_Page * pCurPage =  static_cast<FV_View *>(m_pView)->getCurrentPage();
	PT_DocPosition pos = static_cast<FV_View *>(m_pView)->getPoint();
	bool bStop = false;
	fp_TableContainer *pBroke = pCurPage->getContainingTable(pos);
	if(pBroke == NULL)
	{
	  AP_LeftRulerTableInfo * pTInfo =  NULL;
	  if (pInfo->m_vecTableRowInfo->getItemCount() == 0)
	  {
	      return;
	  }
	  pTInfo = pInfo->m_vecTableRowInfo->getNthItem(0);
	  UT_return_if_fail(pTInfo);
	  fp_CellContainer * pCell = pTInfo->m_pCell;
	  fp_Container * pHdr = pCell->getContainer();
	  while(pHdr && !pHdr->isColumnType())
	  {
	    pHdr = pHdr->getContainer();
	  }
	  if(pHdr == NULL || pHdr->getContainerType() == FP_CONTAINER_COLUMN)
	  {
	        return;
	  }
	  pBroke = static_cast<fp_TableContainer *>(pCell->getContainer());
	  if(pBroke == NULL)
	    return;
	  if(pBroke->getPage() == NULL)
	    return;
	}
	for(i=pInfo->m_iCurrentRow;i <= nrows && !bStop; i++)
	{
		if(m_bValidMouseClick && (m_draggingWhat == DW_CELLMARK) && (i == m_draggingCell ))
		{
			continue;
		}
		_getCellMarkerRects(pInfo,i,rCell,pBroke);
		if(rCell.height > 0)
		{
			_drawCellMark(&rCell,true);
		}
		else
		{
			bStop = true;
		}
	}
	bStop = false;
	for(i=pInfo->m_iCurrentRow;i >= 0 && !bStop; i--)
	{
		if(m_bValidMouseClick && (m_draggingWhat == DW_CELLMARK) && (i == m_draggingCell ))
		{
			continue;
		}
		_getCellMarkerRects(pInfo,i,rCell,pBroke);
		if(rCell.height > 0)
		{
			_drawCellMark(&rCell,true);
		}
		else
		{
			bStop = true;
		}
	}
	xxx_UT_DEBUGMSG(("ap_LeftRuler: Draw Cell Marks end \n"));
}
