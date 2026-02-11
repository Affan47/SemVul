BAapplyBias(
  DdManager *dd,
  DdNode *f,
  DdNode *b,
  ApproxInfo *info,
  DdHashTable *cache)
{
    DdNode *one, *zero, *res;
    DdNode *Ft, *Fe, *B, *Bt, *Be;
    unsigned int topf, topb;
    NodeData *infoF;
    int careT, careE;

    one = DD_ONE(dd);
    zero = Cudd_Not(one);

    if ((infoF = (NodeData *) cuddHashTableGenericLookup(info->table, f)) == NULL)
	return(CARE_ERROR);
    if (f == one) return(TOTAL_CARE);
    if (b == zero) return(infoF->care);
    if (infoF->care == TOTAL_CARE) return(TOTAL_CARE);

    if ((f->ref != 1 || Cudd_Regular(b)->ref != 1) &&
	(res = cuddHashTableLookup2(cache,f,b)) != NULL) {
	if (res->ref == 0) {
	    cache->manager->dead++;
	    cache->manager->constants.dead++;
	}
	return(infoF->care);
    }

    topf = dd->perm[f->index];
    B = Cudd_Regular(b);
    topb = cuddI(dd,B->index);
    if (topf <= topb) {
	Ft = cuddT(f); Fe = cuddE(f);
    } else {
	Ft = Fe = f;
    }
    if (topb <= topf) {

	Bt = cuddT(B); Be = cuddE(B);
	if (Cudd_IsComplement(b)) {
	    Bt = Cudd_Not(Bt);
	    Be = Cudd_Not(Be);
	}
    } else {
	Bt = Be = b;
    }

    careT = BAapplyBias(dd, Ft, Bt, info, cache);
    if (careT == CARE_ERROR)
	return(CARE_ERROR);
    careE = BAapplyBias(dd, Cudd_Regular(Fe), Be, info, cache);
    if (careE == CARE_ERROR)
	return(CARE_ERROR);
    if (careT == TOTAL_CARE && careE == TOTAL_CARE) {
	infoF->care = TOTAL_CARE;
    } else {
	infoF->care = CARE;
    }

    if (f->ref != 1 || Cudd_Regular(b)->ref != 1) {
	ptrint fanout = (ptrint) f->ref * Cudd_Regular(b)->ref;
	cuddSatDec(fanout);
	if (!cuddHashTableInsert2(cache,f,b,one,fanout)) {
	    return(CARE_ERROR);
	}
    }
    return(infoF->care);

}
