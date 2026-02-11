findRange(UT_sint32 iStart, UT_sint32 iEnd,
						UT_sint32& iFirst, UT_sint32& iLast, bool bDontExpand) const
{
	xxx_UT_DEBUGMSG(("fl_Squiggles::findRange(%d, %d)\n", iStart, iEnd));

	UT_sint32 iSquiggles = _getCount();
	if (0 == iSquiggles) return false;
	fl_PartOfBlock* pPOB = 0;
	UT_sint32 s, e;

	if((getSquiggleType() == FL_SQUIGGLE_GRAMMAR) && !bDontExpand)
	{


	  UT_sint32 i = 0;
	  for(i=0; i< iSquiggles;i++)
	  {
	    pPOB = getNth(i);
	    if((iStart >= pPOB->getOffset()) && (iStart <= pPOB->getOffset() + pPOB->getPTLength()) && pPOB->isInvisible())
	    {
	      iStart = pPOB->getOffset();
	    }
	    if((iEnd  >= pPOB->getOffset()) && (iEnd <= pPOB->getOffset() + pPOB->getPTLength()) && pPOB->isInvisible())
	    {
	      iEnd = pPOB->getOffset() + pPOB->getPTLength();
	    }
	  }
	}

	_findFirstAfter(iEnd, e);


	if (0 == e)
	{
	  UT_ASSERT(getNth(0)->getOffset() > iEnd);
	  return false;
	}

	e--;


	for (s = e; s >= 0; s--)
	{
	  pPOB = getNth(s);
	  if ((pPOB->getOffset() + pPOB->getPTLength()) < iStart) break;
	}


	if (s == e)
	{
	  UT_ASSERT((pPOB->getOffset() + pPOB->getPTLength()) < iStart);
	  return false;
	}

	s++;
	UT_ASSERT(s >= 0 && s < iSquiggles);
	UT_ASSERT(e >= 0 && e < iSquiggles);
	UT_ASSERT(s <= e);

	iFirst = s;
	iLast = e;

	return true;
}
