hasMath(void)
{
	pf_Frag *  pf = getPieceTable()->getFragments().getFirst();
	while(pf)
	{
		if(pf->getType() == pf_Frag::PFT_Object)
		{
			pf_Frag_Object * po = (pf_Frag_Object*) pf;
			if(po->getObjectType() == PTO_Math)
			{
				return true;
			}
		}
		pf = pf->getNext();
	}
	return false;
}
