c_ekkftjl_sparse2(COIN_REGISTER2 const EKKfactinfo * COIN_RESTRICT2 fact,
		    double * COIN_RESTRICT dwork1,
		    int * COIN_RESTRICT mpt,
		    int nincol)
{
  double tolerance = fact->zeroTolerance;
  const double * COIN_RESTRICT dluval = fact->R_etas_element+1;
  const int * COIN_RESTRICT hrowi = fact->R_etas_index+1;
  const int * COIN_RESTRICT mcstrt = fact->R_etas_start;
  int ndo=fact->nR_etas;
  const int * COIN_RESTRICT hpivco = fact->hpivcoR;
  int i;
  int knext;
  int ipiv;
  double dv;


  if (ndo != 0) {
    knext = mcstrt[1];
    for (i = 1; i <= ndo; ++i) {
      int k1 = knext;
      int iel;
      ipiv = hpivco[i];
      dv = dwork1[ipiv];
      bool onList = (dv!=0.0);
      knext = mcstrt[i + 1];

      for (iel = knext ; iel < k1; ++iel) {
	int irow = hrowi[iel];
	dv += SHIFT_REF(dwork1, irow) * dluval[iel];
      }


      if (onList) {
	if (fabs(dv) > tolerance) {
	  dwork1[ipiv]=dv;
	} else {
	  dwork1[ipiv] = 1.0e-128;
	}
      } else {
	if (fabs(dv) > tolerance) {

	  mpt[nincol++]=ipiv;
	  dwork1[ipiv]=dv;
	}
      }
    }
  }
  knext=0;
  for (i=0; i<nincol; i++) {
    ipiv=mpt[i];
    dv=dwork1[ipiv];
    if (fabs(dv) > tolerance) {
      mpt[knext++]=ipiv;
    } else {
      dwork1[ipiv]=0.0;
    }
  }
  return knext;
}
