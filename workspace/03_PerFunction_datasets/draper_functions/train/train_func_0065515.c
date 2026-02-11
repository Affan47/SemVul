cuddVerifySol(
  DdManager * bdd,
  DdNode * F ,
  DdNode ** G ,
  int * yIndex ,
  int  n )
{
    DdNode *w, *R;

    int j;

    R = F;
    cuddRef(R);
    for(j = n - 1; j >= 0; j--) {
	 w = Cudd_bddCompose(bdd, R, G[j], yIndex[j]);
	if (w) {
	    cuddRef(w);
	} else {
	    return(NULL);
	}
	Cudd_RecursiveDeref(bdd,R);
	R = w;
    }

    cuddDeref(R);

    return(R);

}
