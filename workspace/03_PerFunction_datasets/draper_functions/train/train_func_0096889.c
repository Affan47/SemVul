simplePrimTintegral(const DistributionSpecStruct& prim1,
		    const DistributionSpecStruct& prim2,
		    int coord,
		    ergo_real threshold)
{
  const int maxDistrsInTempList = 888;
  DistributionSpecStruct tempList[maxDistrsInTempList];
  int i, k, nNewPrims;
  ergo_real sum;
  DistributionSpecStruct list1[2];
  DistributionSpecStruct list2[4];
  do_derivative_of_simple_prim(prim2, list1, coord);
  if(list1[0].coeff != 0)
    {
      do_derivative_of_simple_prim(list1[0], &list2[0], coord);
    }
  else
    {
      list2[0].coeff = 0;
      list2[1].coeff = 0;
    }
  if(list1[1].coeff != 0)
    {
      do_derivative_of_simple_prim(list1[1], &list2[2], coord);
    }
  else
    {
      list2[2].coeff = 0;
      list2[3].coeff = 0;
    }


  sum = 0;
  for(i = 0; i < 4; i++)
    {
      if(list2[i].coeff == 0)
	continue;

      nNewPrims = get_product_simple_prims(prim1,
					   list2[i],
					   tempList,
					   maxDistrsInTempList,
					   threshold);
      if(nNewPrims < 0)
	{
	  do_output(LOG_CAT_ERROR, LOG_AREA_INTEGRALS, "error in get_product_simple_prims");
	  return -1;
	}

      for(k = 0; k < nNewPrims; k++)
	{
	  DistributionSpecStruct* currDistr = &tempList[k];
	  sum += compute_integral_of_simple_prim(currDistr);
	}
    }

  return sum;
}
