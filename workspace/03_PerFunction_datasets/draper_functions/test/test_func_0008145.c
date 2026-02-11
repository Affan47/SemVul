simplifDcZeroBdd (pGon, pGdc)
     pNode pGon, pGdc;
{
  pNode pBddLoc;
  pNode pAOH, pAOL;


  if (pGdc == zero)
    return (pGon);
  if (pGon->index < 2)
    return (pGon);

  pBddLoc = searchTabLoc (sysBdd.pMC, pGon, pGdc, DONTCARE0);
  if (pBddLoc != NULL)
    return (pBddLoc);


  if (pGdc->index == pGon->index)
    {


      if (pGdc->high == one)
	return (simplifDcZeroBdd (pGon->low, pGdc->low));
      if (pGdc->low == one)
	return (simplifDcZeroBdd (pGon->high, pGdc->high));


      if (pGon->high == zero && applyBinBdd (AND, pGon->low, pGdc->high) == pGon->low)
	return (pGon->low);

      if (pGon->low == zero && applyBinBdd (AND, pGon->high, pGdc->low) == pGon->high)
	return (pGon->high);

      pAOH = applyBinBdd (AND, pGon->high, applyBinBdd (OR, pGon->low, pGdc->low));
      pAOL = applyBinBdd (AND, pGon->low, applyBinBdd (OR, pGon->high, pGdc->high));

      if (pAOH == pGon->high && pAOL == pGon->low)
	{
	  pBddLoc = simplifDcZeroBdd (applyBinBdd (OR, pGon->low, pGon->high),
				  applyBinBdd (AND, pGdc->low, pGdc->high));
	}
      else
	{


	  pBddLoc = initVertexBdd (pGon->index,
				   simplifDcZeroBdd (pGon->high, pGdc->high),
				   simplifDcZeroBdd (pGon->low, pGdc->low));

	}
    }
  else


  if (pGon->index > pGdc->index)
    pBddLoc = initVertexBdd (pGon->index, simplifDcZeroBdd (pGon->high, pGdc),
			     simplifDcZeroBdd (pGon->low, pGdc));
  else
    pBddLoc = simplifDcZeroBdd (pGon, applyBinBdd (AND, pGdc->low, pGdc->high));

  addTabLoc (sysBdd.pMC, pGon, pGdc, pBddLoc, DONTCARE0);
  return (pBddLoc);
}
