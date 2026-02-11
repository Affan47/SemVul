upVarBdd (pF, pFoldIndex, newIndex)
     pNode pF, pFoldIndex;
     short newIndex;
{
  pNode pBddLoc;

  pBddLoc = searchTabLoc (sysBdd.pMC, pF, pFoldIndex, newIndex + 10);
  if (pBddLoc != NULL)
    return (pBddLoc);

  if (pF->index < pFoldIndex->index)
    return (pF);
  if (pF->index > newIndex)
    pBddLoc = initVertexBdd (pF->index, upVarBdd (pF->high, pFoldIndex, newIndex),
			     upVarBdd (pF->low, pFoldIndex, newIndex));
  else


    pBddLoc = initVertexBdd (newIndex,
			     constraintBdd (pF, pFoldIndex),
			     constraintBdd (pF, notBdd (pFoldIndex)));
  addTabLoc (sysBdd.pMC, pF, pFoldIndex, pBddLoc, newIndex + 10);
  return (pBddLoc);
}
