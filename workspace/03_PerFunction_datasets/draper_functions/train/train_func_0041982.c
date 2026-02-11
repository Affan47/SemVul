cuddNodeArrayRecur(
  DdNode *f,
  DdNodePtr *table,
  int index)
{
    int tindex, eindex;

    if (!Cudd_IsComplement(f->next)) {
	return(index);
    }

    f->next = Cudd_Regular(f->next);
    if (cuddIsConstant(f)) {
	table[index] = f;
	return(index + 1);
    }
    tindex = cuddNodeArrayRecur(cuddT(f), table, index);
    eindex = cuddNodeArrayRecur(Cudd_Regular(cuddE(f)), table, tindex);
    table[eindex] = f;
    return(eindex + 1);

}
