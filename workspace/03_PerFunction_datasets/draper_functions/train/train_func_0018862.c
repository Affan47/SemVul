do_merge_sort_distrs(int n,
		     DistributionSpecStruct* list,
		     DistributionSpecStruct* workList)
{


  int n1, n2, nn, decision, i1, i2, i;
  DistributionSpecStruct* d1;
  DistributionSpecStruct* d2;

  if(n == 0)
    return 0;

  if(n < 1)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "(n < 1)");
      return -1;
    }
  if(n == 1)
    return 0;

  n1 = n / 2;
  n2 = n - n1;


  if(do_merge_sort_distrs(n1, list, workList) != 0)
    return -1;


  if(do_merge_sort_distrs(n2, &list[n1], workList) != 0)
    return -1;


  nn = 0;
  i1 = 0;
  i2 = 0;
  while(nn < n)
    {
      if((i1 < n1) && (i2 < n2))
	{

	  d1 = &list[i1];
	  d2 = &list[n1+i2];
	  decision = 0;
	  for(i = 0; i < 3; i++)
	    {
	      if(decision == 0)
		{
		  if(d1->monomialInts[i] != d2->monomialInts[i])
		    {
		      if(d1->monomialInts[i] > d2->monomialInts[i])
			decision = 1;
		      else
			decision = 2;
		    }
		}
	    }
	  if(decision == 0)
	    {

	      if(d1->exponent > d2->exponent)
		decision = 1;
	      else
		decision = 2;
	    }
	}
      else
	{
	  if(i1 == n1)
	      decision = 2;
	  else
	      decision = 1;
	}
      if(decision <= 0)
	{
	  do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "(decision <= 0)");
	  return -1;
	}
      if(decision == 1)
	{
	  memcpy(&workList[nn], &list[i1], sizeof(DistributionSpecStruct));
	  i1++;
	}
      else
	{
	  memcpy(&workList[nn], &list[n1+i2], sizeof(DistributionSpecStruct));
	  i2++;
	}
      nn++;
    }
  if(i1 != n1)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "(i1 != n1)");
      return -1;
    }
  if(i2 != n2)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "(i2 != n2)");
      return -1;
    }
  if(nn != n)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "(nn != n)");
      return -1;
    }
  memcpy(list, workList, n * sizeof(DistributionSpecStruct));
  return 0;
}
