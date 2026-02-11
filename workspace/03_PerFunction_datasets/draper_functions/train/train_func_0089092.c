getBookmark(pf_Frag_Strux* sdh, UT_uint32 offset)
{
	const pf_Frag * pf = static_cast<const pf_Frag *>(sdh);
	UT_return_val_if_fail (pf->getType() == pf_Frag::PFT_Strux, NULL);
	const pf_Frag_Strux * pfsBlock = static_cast<const pf_Frag_Strux *> (pf);
	UT_return_val_if_fail (pfsBlock->getStruxType() == PTX_Block, NULL);

	UT_uint32 cumOffset = 0;
	pf_Frag_Object * pfo = NULL;
	for (pf_Frag * pfTemp=pfsBlock->getNext(); (pfTemp); pfTemp=pfTemp->getNext())
	{
		cumOffset += pfTemp->getLength();
		if (offset < cumOffset)
		{
			switch (pfTemp->getType())
			{
				case pf_Frag::PFT_Object:
					pfo = static_cast<pf_Frag_Object *> (pfTemp);
					return pfo->getBookmark();
				default:
					return NULL;
			}
		}

	}
	return NULL;
}
