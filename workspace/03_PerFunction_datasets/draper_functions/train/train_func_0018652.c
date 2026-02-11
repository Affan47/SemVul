get_no_of_primitives_for_density(ergo_real cutoff,
				 const ergo_real *dmat,
				 const BasisInfoStruct & basisInfo)
{
#define MAX_DISTR_IN_TEMP_LIST 888

  int i, j;
  int symmetryFactor;
  int nBasisFuncs, nn;

  nBasisFuncs = basisInfo.noOfBasisFuncs;
  nn = 0;
  for(i = 0; i < nBasisFuncs; i++)
    {
      for(j = 0; j < nBasisFuncs; j++)
	{
	  DistributionSpecStruct tempList[MAX_DISTR_IN_TEMP_LIST];
	  int nPrimitives, k;


	  if(i == j)
              symmetryFactor = 1;
	  else
	    symmetryFactor = 2;
	  if(i > j)
	    continue;
          nPrimitives =
	    get_product_simple_primitives(basisInfo, i,
					  basisInfo, j,
					  tempList,
					  MAX_DISTR_IN_TEMP_LIST,
					  0);
	  if(nPrimitives <= 0)
	    {
	      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in get_product_simple_primitives");
	      return -1;
	    }
	  for(k = 0; k < nPrimitives; k++)
	    {
	      DistributionSpecStruct* currDistr = &tempList[k];
	      ergo_real Mij = dmat[i*nBasisFuncs+j];
	      ergo_real newCoeff = currDistr->coeff * Mij * symmetryFactor;
	      if(std::fabs(newCoeff) > cutoff)
		nn++;
	    }
	}
    }
  return nn;
}
