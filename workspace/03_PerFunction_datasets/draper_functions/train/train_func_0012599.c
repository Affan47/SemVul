liftAndUncomplementAndAdd(
					    double ,
         CoinPackedVector & krow,
         double & b,
         int * complement,
         int ,
         CoinPackedVector & cover,
         CoinPackedVector & remainder,
         OsiCuts & cs )
{
  CoinPackedVector cut;
  double cutRhs = cover.getNumElements() - 1.0;
  int goodCut=1;

  if (remainder.getNumElements() > 0){

    if (!liftCoverCut(
		      b, krow.getNumElements(),
		      cover, remainder,
		      cut ))
      goodCut= 0;
  }


  else {
    cut.reserve(cover.getNumElements());
    cut.setConstant(cover.getNumElements(),cover.getIndices(),1.0);
  }

  if (goodCut) {

    int k;

    double * elements = cut.getElements();
    int * indices = cut.getIndices();
    for (k=0; k<cut.getNumElements(); k++){
      if (complement[indices[k]]) {


        elements[k] *= -1;
        cutRhs += elements[k];
      }
    }


    OsiRowCut rc;
    rc.setRow(cut);
#ifdef CGL_DEBUG
    {
      double * elements = cut.getElements();
      int * indices = cut.getIndices();
      int n=cut.getNumElements();
      for (k=0; k<n; k++){
	assert(indices[k]>=0);
	assert(elements[k]);
        assert (fabs(elements[k])>1.0e-12);
      }
    }
#endif
    rc.setLb(-COIN_DBL_MAX);
    rc.setUb(cutRhs);


#ifdef PRINT_DEBUG
    {
      int k;
      printf("cutrhs %g %d elements\n",cutRhs,cut.getNumElements());
      double * elements = cut.getElements();
      int * indices = cut.getIndices();
      for (k=0; k<cut.getNumElements(); k++){
	printf("%d %g\n",indices[k],elements[k]);
      }
    }
#endif
    cs.insert(rc);

    return 1;
  } else {
    return 0;
  }
}
