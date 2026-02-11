PE10main(pe_data_t *pedata)
{

  unsigned long int x;
  unsigned long long total = 2;

  for(x = 3; x <= UPPERLIMIT; x+=2)
    {
      if (IsPrime(x))
	{

	  total = total + x;

	}

    }

    if (pedata->verbosity > 0) printf ("Total: %llu\n", total);
    sprintf(pedata->result,"%llu",total);

    return 0;
}
