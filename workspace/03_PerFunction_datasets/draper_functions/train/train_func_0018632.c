deleteHdrFtrStrux(pf_Frag_Strux * pfs)
{
	UT_return_if_fail( pfs );

	if(m_pDocument->isMarkRevisions())
	{
		const pf_Frag * pfFrag = pfs;
		PT_DocPosition dpos1 = getFragPosition(pfFrag);

		pfFrag = pfFrag->getNext();

		while(pfFrag)
		{
			if((pfFrag->getType() == pf_Frag::PFT_EndOfDoc) ||
			   (pfFrag->getType() == pf_Frag::PFT_Strux &&
				static_cast<const pf_Frag_Strux*>(pfFrag)->getStruxType() == PTX_SectionHdrFtr))
			{
				break;
			}

			pfFrag = pfFrag->getNext();
		}


		UT_return_if_fail( pfFrag );

		PT_DocPosition dpos2 = getFragPosition(pfFrag);

		UT_uint32 iRealDelete = 0;
		deleteSpan(dpos1, dpos2, NULL, iRealDelete, true , false );
	}
	else
	{
		const PP_AttrProp * pAP = NULL;
		UT_return_if_fail(pfs->getStruxType()==PTX_SectionHdrFtr);
		pf_Frag_Strux_SectionHdrFtr * pfHdr = static_cast<pf_Frag_Strux_SectionHdrFtr *>(pfs);

		if(!getAttrProp(pfHdr->getIndexAP(),&pAP) || !pAP)
			return;

		const gchar * pszHdrId;
		if(!pAP->getAttribute("id", pszHdrId) || !pszHdrId)
			return;

		const gchar * pszHdrType;
		if(!pAP->getAttribute("type", pszHdrType) || !pszHdrType)
			return;

		_realDeleteHdrFtrStrux(pfs);
		_fixHdrFtrReferences(pszHdrType, pszHdrId);
	}

}
