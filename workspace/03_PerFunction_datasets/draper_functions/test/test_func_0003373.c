tryAddConcept ( const CWDArray& lab, BipolarPointer bp, const DepSet& dep )
{

	register const BipolarPointer inv_p = inverse(bp);
	bool canC = isUsed(bp);
	bool canNegC = isUsed(inv_p);


	if ( canC )
	{
		if ( canNegC )
			return checkAddedConcept ( lab, bp, dep );
		else
			return findConcept ( lab, bp ) ? acrExist : acrDone;
	}
	else
	{
		if ( canNegC )
			return findConceptClash ( lab, inv_p, dep ) ? acrClash : acrDone;
		else
			return acrDone;
	}
}
