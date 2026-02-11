insertStruxBeforeFrag(pf_Frag * pF, PTStruxType pts,
										  const gchar ** attributes, pf_Frag_Strux ** ppfs_ret)
{
	UT_return_val_if_fail(pF , false);

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

	m_fragments.insertFragBefore(pF, pfs);
	if (ppfs_ret)
		*ppfs_ret = pfs;

	if ((pts == PTX_EndFootnote) || (pts == PTX_EndEndnote) || (pts == PTX_EndAnnotation))
	{
		_insertNoteInEmbeddedStruxList(pfs);
	}

	return true;
}
