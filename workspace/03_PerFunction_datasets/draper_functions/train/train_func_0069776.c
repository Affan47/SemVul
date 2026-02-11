updateLayout(bool bDoFull)
{
	fl_ContainerLayout*	pBL = getFirstLayout();
	FV_View * pView = m_pLayout->getView();
	bool bShowHidden = pView && pView->getShowPara();
	FPVisibility eHidden;
	bool bHidden;


	bDoFull = true;
	UT_DEBUGMSG(("Doing DocSection Update layout (section %p)\n",this));
	if (!bDoFull || (m_vecFormatLayout.getItemCount() > 0))
	{
	        UT_sint32 i =0;
		UT_sint32 j = 0;
		UT_sint32 count = m_vecFormatLayout.getItemCount();
		for(i=0; i<count; i++)
		{
		        if(j >= m_vecFormatLayout.getItemCount())
			    break;
		        pBL = m_vecFormatLayout.getNthItem(j);
			j++;
		        eHidden  = pBL->isHidden();
			bHidden = ((eHidden == FP_HIDDEN_TEXT && !bShowHidden)
				   || eHidden == FP_HIDDEN_REVISION
				   || eHidden == FP_HIDDEN_REVISION_AND_TEXT);

			if(!bHidden)
			{
			  xxx_UT_DEBUGMSG(("container %x type %s needformat %d \n",pBL,pBL->getContainerString(),pBL->needsReformat()));
			     if (pBL->needsReformat())
			     {
			          if(!(m_pLayout->isLayoutFilling() && pBL->getContainerType() == FL_CONTAINER_TOC))
				  {
				       pBL->format();
				       j--;
				       if(j < m_vecFormatLayout.getItemCount())
				       {
					    UT_sint32 k = m_vecFormatLayout.findItem(pBL);
					    if(k == j)
					         m_vecFormatLayout.deleteNthItem(j);
				       }
				  }
			     }
			     if (pBL->getContainerType() != FL_CONTAINER_BLOCK && !getDocument()->isDontImmediateLayout())
			     {
			          pBL->updateLayout(false);
			     }
			}

		}
	}
	else if(bDoFull)
	{
	        while (pBL)
		{
		        eHidden  = pBL->isHidden();
			bHidden = ((eHidden == FP_HIDDEN_TEXT && !bShowHidden)
				   || eHidden == FP_HIDDEN_REVISION
				   || eHidden == FP_HIDDEN_REVISION_AND_TEXT);

			if(!bHidden)
			{
			     if (pBL->needsReformat())
			     {
			          if(!(m_pLayout->isLayoutFilling() && pBL->getContainerType() == FL_CONTAINER_TOC))
				  {
				       pBL->format();
				  }
			     }
			     if (pBL->getContainerType() != FL_CONTAINER_BLOCK && !getDocument()->isDontImmediateLayout())
			     {
			          pBL->updateLayout(false);
			     }
			}

			pBL = pBL->getNext();
		}
	}
	m_vecFormatLayout.clear();
	if(needsSectionBreak() && !getDocument()->isDontImmediateLayout() )
	{
		if (!isFirstPageValid())
		{


			collapse();
			format();
			return;
		}
		m_ColumnBreaker.breakSection();
	}
	if(needsRebuild() && !getDocument()->isDontImmediateLayout() )
	{
		checkAndRemovePages();
		addValidPages();
	}
}
