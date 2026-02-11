populateStrux(pf_Frag_Strux* sdh,
									  const PX_ChangeRecord * pcr,
									  fl_ContainerLayout* * psfh)
{
	UT_ASSERT(m_pTOCL);

	UT_ASSERT(pcr->getType() == PX_ChangeRecord::PXT_InsertStrux);
	PT_AttrPropIndex iTOC = m_pStyle->getIndexAP();
	const PX_ChangeRecord_Strux * pcrx = static_cast<const PX_ChangeRecord_Strux *> (pcr);
	m_bListening = true;
	fl_BlockLayout * pMyBL = m_pPrevBL;
	if(pMyBL == NULL)
	{
		pMyBL = static_cast<fl_BlockLayout *>(m_pTOCL->getFirstLayout());
	}
	switch (pcrx->getStruxType())
	{
	case PTX_Block:
	{
		if (m_bListening)
		{

			fl_ContainerLayout*	pBL = m_pTOCL->insert(sdh,pMyBL, iTOC,FL_CONTAINER_BLOCK);
			if (!pBL)
			{
				UT_DEBUGMSG(("no memory for BlockLayout"));
				return false;
			}
			m_pCurrentBL = pBL;
			*psfh = pBL;
		}

	}
	break;

	default:
		UT_ASSERT(0);
		return false;
	}


	return true;
}
