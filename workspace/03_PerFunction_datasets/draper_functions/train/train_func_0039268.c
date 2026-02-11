pdb_getproc(int pid, time_t btime, struct pinfo **pinfopp)
{
	register struct pinfo	*pp;

	pp = phash[pid&(NPHASH-1)];


	while (pp)
	{


		if (pp->pstat.gen.pid == pid && pp->pstat.gen.btime == btime)
		{
			if (pp->prnext)
			{
				(pp->prnext)->prprev = pp->prprev;
				(pp->prprev)->prnext = pp->prnext;
			}

			pp->prnext = NULL;
			pp->prprev = NULL;

			*pinfopp = pp;

			return(1);
		}

		pp = pp->phnext;
	}


	return(0);
}
