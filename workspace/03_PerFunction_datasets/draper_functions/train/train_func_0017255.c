appendStrux(PTStruxType pts, const gchar ** attributes, pf_Frag_Strux ** ppfs_ret)
{
	pf_Frag_Strux * pfs = NULL;
	if(!_makeStrux(pts, attributes, pfs) || !pfs)
		return false;

	if(attributes)
	{
		const gchar * pXID = UT_getAttribute(PT_XID_ATTRIBUTE_NAME, attributes);
		UT_uint32 iXID = 0;
		if(pXID && *pXID)
		{
			iXID = atoi(pXID);
			pfs->setXID(iXID);
		}
	}

	pf_Frag * pfPrev = m_fragments.getLast();
	bool bDoInsertFmt = false;
	if(pfPrev != NULL && pfPrev->getType() == pf_Frag::PFT_Strux)
	{
		pf_Frag_Strux * pfsPrev = static_cast<pf_Frag_Strux *>(pfPrev);
		if(pfsPrev->getStruxType() == PTX_Block)
		{
			bDoInsertFmt = true;
		}
	}
	m_fragments.appendFrag(pfs);

	if ((pts == PTX_EndFootnote) || (pts == PTX_EndEndnote) || (pts == PTX_EndAnnotation))
	{
		_insertNoteInEmbeddedStruxList(pfs);
	}

	if(bDoInsertFmt)
	{
		insertFmtMarkBeforeFrag(static_cast<pf_Frag *>(pfs));
	}
	if (ppfs_ret)
		*ppfs_ret = pfs;
	return true;
}
