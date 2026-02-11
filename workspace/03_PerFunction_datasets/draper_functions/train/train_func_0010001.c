PrintQueryTuples(const PGresult *results)
{
	printQueryOpt my_popt = pset.popt;


	if (pset.gfname)
	{

		FILE	   *queryFout_copy = pset.queryFout;
		bool		queryFoutPipe_copy = pset.queryFoutPipe;

		pset.queryFout = stdout;


		if (!setQFout(pset.gfname))
		{
			pset.queryFout = queryFout_copy;
			pset.queryFoutPipe = queryFoutPipe_copy;
			return false;
		}

		printQuery(results, &my_popt, pset.queryFout, pset.logfile);


		setQFout(NULL);

		pset.queryFout = queryFout_copy;
		pset.queryFoutPipe = queryFoutPipe_copy;

		free(pset.gfname);
		pset.gfname = NULL;
	}
	else
		printQuery(results, &my_popt, pset.queryFout, pset.logfile);

	return true;
}
