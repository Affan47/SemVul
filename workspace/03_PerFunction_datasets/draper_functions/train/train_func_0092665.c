sizeRequest(fp_Requisition * pRequisition)
{
  UT_sint32 row, col;

  pRequisition->width = 0;
  pRequisition->height = 0;
  bool bDefinedColWidth = false;
  fl_TableLayout * pTL = static_cast<fl_TableLayout *>(getSectionLayout());
  const UT_GenericVector<fl_ColProps *> * pVecColProps = pTL->getVecColProps();
  if(pVecColProps->getItemCount() > 0)
  {
	  bDefinedColWidth = true;
  }
  _size_request_init ();
  _size_request_pass1 ();
  _size_request_pass2 ();
  _size_request_pass3 ();
  _size_request_pass2 ();

  m_iCols = m_vecColumns.getItemCount();
  for (col = 0; col < m_iCols; col++)
  {
	  if(bDefinedColWidth && (col < pVecColProps->getItemCount()) )
	  {
		  fl_ColProps * pColProp = pVecColProps->getNthItem(col);
		  getNthCol(col)->requisition = pColProp->m_iColWidth;
	  }
	  pRequisition->width += getNthCol(col)->requisition;
  }
  for (col = 0; col + 1 < m_iCols; col++)
  {
	  pRequisition->width += getNthCol(col)->spacing;
  }

  for (row = 0; row < m_iRows; row++)
  {
	  fp_TableRowColumn * pRow = getNthRow(row);
	  UT_sint32 iOldReq = pRow->requisition;
	  UT_sint32 iNewReq = getRowHeight(row,iOldReq);
	  if(iNewReq > iOldReq)
	  {
		  iNewReq -= pRow->spacing;
	  }
	  pRow->requisition = iNewReq;
	  pRequisition->height += getNthRow(row)->requisition;
	  if (row < m_iRows - 1)
	  {
		  pRequisition->height += pRow->spacing;
	  }
  }
  pRequisition->height += 2 * m_iBorderWidth;
  xxx_UT_DEBUGMSG(("SEVIOR: requisition height %d \n", pRequisition->height));
}
