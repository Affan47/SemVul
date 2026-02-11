_computeBlockOffset(pf_Frag_Strux * pfs,pf_Frag * pfTarget) const
{


	UT_uint32 sum;
	pf_Frag * pf;

	for (pf=pfs->getNext(), sum=0; (pf && (pf!=pfTarget)); sum+=pf->getLength(), pf=pf->getNext())
		;
	if(pf == NULL)
	{
		return 0;
	}

	return sum;
}
