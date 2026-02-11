sizeRequest(fp_Requisition * pRequest)
{
	xxx_UT_DEBUGMSG(("Doing size request on %x \n",pRequest));
	UT_sint32 count = countCons();
	UT_sint32 i =0;
	UT_sint32 height = 0;
	UT_sint32 width = 0;
	for(i=0 ; i < count; i++)
	{
		fp_Container * pCon = static_cast<fp_Container *>(getNthCon(i));
		if(pCon->getContainerType() == FP_CONTAINER_LINE)
		{
			static_cast<fp_Line *>(pCon)->recalcHeight();
			if(width < pCon->getWidth())
			{
				width = pCon->getWidth();

			}
			xxx_UT_DEBUGMSG(("sizeRequest: Height of Line %d %d tot %d \n",i,pCon->getHeight(),height));
			height = height + pCon->getHeight();
			height = height + pCon->getMarginAfter();
		}
		else
		{
			if(pCon->getContainerType() == FP_CONTAINER_TABLE)
			{
				fp_TableContainer * pTab = static_cast<fp_TableContainer*>(pCon);
				fl_TableLayout * pTL = static_cast<fl_TableLayout *>(pTab->getSectionLayout());
				if (pTL->isInitialLayoutCompleted())
				{
					fp_Requisition pReq;
					pTab->sizeRequest(&pReq);
					if(width < pReq.width)
					{
						width = pReq.width;
					}
					height = height + pReq.height;
				}
			}
			else
			{
				UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
			}
		}
		xxx_UT_DEBUGMSG(("Total height %d \n",height));
	}
	UT_sint32 maxwidth = 0;
	fl_CellLayout * pCellL = static_cast<fl_CellLayout *>(getSectionLayout());
	fl_ContainerLayout * pCL = pCellL->getFirstLayout();
	while(pCL)
	{
		if(pCL->getContainerType() == FL_CONTAINER_BLOCK)
		{
			fl_BlockLayout * pBL = static_cast<fl_BlockLayout *>(pCL);
			UT_sint32 iw = pBL->getMaxNonBreakableRun();
			if(maxwidth < iw)
			{
				maxwidth = iw;
			}
		}
		pCL = pCL->getNext();
	}

	if(maxwidth > width)
	{
		width = maxwidth;
	}
	if(pRequest)
	{
		pRequest->width = width;
		pRequest->height = height;
	}

	fp_Column * pCol = static_cast<fp_Column *>(fp_Container::getColumn());
	if(pCol && (width == 0))
	{
		width = pCol->getWidth();
	}

	m_MyRequest.width = width;
	m_MyRequest.height = height;
	xxx_UT_DEBUGMSG(("Size Request: Cell Total height  %d width %d \n",height,width));
}
