notify(AV_View * pView, const AV_ChangeMask mask)
  {
	  GR_Graphics *pG = static_cast<FV_View *>(pView)->getGraphics();

	  if (m_pFrame && (mask & (AV_CHG_INSERTMODE)))
      {
		  AP_FrameData * pData = static_cast<AP_FrameData *>(m_pFrame->getFrameData());
		  if (pData)
		  {
			  pG->allCarets()->setInsertMode(pData->m_bInsertMode);
			  return true;
		  }
      }

	  if (


		  ((mask & AV_CHG_KEYPRESSED) ||
	  		(mask & AV_CHG_TYPING) ||
		   (mask & AV_CHG_MOTION) ) && pG->allCarets()->getBaseCaret()
	     )
      {
		  pG->allCarets()->getBaseCaret()->resetBlinkTimeout();
		  return true;
      }

	  return false;
  }
