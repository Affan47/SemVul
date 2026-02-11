rememberFrame(XAP_Frame * pFrame, XAP_Frame * pCloneOf)
{
	UT_ASSERT(pFrame);


	m_vecFrames.addItem(pFrame);

	if(! m_lastFocussedFrame)
	    rememberFocussedFrame(pFrame);


	if (pCloneOf)
	{

		CloneMap::const_iterator iter = m_hashClones.find(pCloneOf->getViewKey());

		UT_GenericVector<XAP_Frame*> * pvClones = NULL;

		if (iter != m_hashClones.end())
		{
			UT_GenericVector<XAP_Frame*> * pEntry = iter->second;


			pvClones = pEntry;

			if (!pvClones)
			{

				pvClones = new UT_GenericVector<XAP_Frame*>();
				UT_return_val_if_fail(pvClones,false);

				pvClones->addItem(pCloneOf);


				m_hashClones[pCloneOf->getViewKey()] = pvClones;
			}
		}
		else
		{

			pvClones = new UT_GenericVector<XAP_Frame*>();
			UT_return_val_if_fail(pvClones,false);

			pvClones->addItem(pCloneOf);


			m_hashClones.insert(std::make_pair(pCloneOf->getViewKey(), pvClones));
		}

		pvClones->addItem(pFrame);


		for (UT_sint32 j=0; j<pvClones->getItemCount(); j++)
		{
			XAP_Frame * f = pvClones->getNthItem(j);
			UT_continue_if_fail(f);

			f->setViewNumber(j+1);

			if (f != pFrame)
				f->updateTitle();
		}
	}


	notifyFrameCountChange();
	return true;
}
