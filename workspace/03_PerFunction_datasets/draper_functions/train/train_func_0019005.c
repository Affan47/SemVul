_insertFmtMark(pf_Frag * pf, UT_uint32 fragOffset, PT_AttrPropIndex api)
{
	pf_Frag_FmtMark * pffm = new pf_Frag_FmtMark(this,api);
	if (!pffm)
		return false;

	if (fragOffset == 0)
	{


		m_fragments.insertFrag(pf->getPrev(),pffm);
	}
	else if (fragOffset == pf->getLength())
	{


		m_fragments.insertFrag(pf,pffm);
	}
	else
	{


		UT_return_val_if_fail (pf->getType() == pf_Frag::PFT_Text,false);
		pf_Frag_Text * pft = static_cast<pf_Frag_Text *>(pf);
		UT_uint32 lenTail = pft->getLength() - fragOffset;
		PT_BufIndex biTail = m_varset.getBufIndex(pft->getBufIndex(),fragOffset);
		pf_Frag_Text * pftTail = new pf_Frag_Text(this,biTail,lenTail,pft->getIndexAP(),pft->getField());
		if (!pftTail)
			goto MemoryError;

		pft->changeLength(fragOffset);
		m_fragments.insertFrag(pft,pffm);
		m_fragments.insertFrag(pffm,pftTail);
	}

	return true;

MemoryError:
	DELETEP(pffm);
	return false;
}
