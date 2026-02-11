checkForSuspect(void)
{
	pf_Frag * pf = getLastFrag();
	if(pf == NULL)
	{
		return true;
	}
	if(pf->getType() == pf_Frag::PFT_Strux)
	{
		pf_Frag_Strux * pfs = static_cast<pf_Frag_Strux *>(pf);
		if((pfs->getStruxType() != PTX_Block) && (pfs->getStruxType() != PTX_EndFootnote) && (pfs->getStruxType() != PTX_EndEndnote) && (pfs->getStruxType() != PTX_EndAnnotation) )
		{


			m_vecSuspectFrags.addItem(pf);
			return true;
		}

	}
	return true;
}
