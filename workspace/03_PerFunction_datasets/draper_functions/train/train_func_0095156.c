pdb_cleanresidue(void)
{
	register struct pinfo	*pr;
	register int		pid;


	pr = presidue.prnext;

	while (pr != &presidue)
	{
		pid = pr->pstat.gen.pid;

		pr  = pr->prnext;

		pdb_delproc(pid);
	}

	return(1);
}
