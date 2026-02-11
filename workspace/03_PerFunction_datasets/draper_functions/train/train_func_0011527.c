log_conflicts()
{
    register int i;

    fprintf(verbose_file, "\n\n");
    for (i = 0; i < nstates; i++)
    {
	if (SRconflicts[i] || RRconflicts[i])
	{
	    fprintf(verbose_file, "State %d contains ", i);
	    if (SRconflicts[i] == 1)
		fprintf(verbose_file, "1 shift/reduce conflict");
	    else if (SRconflicts[i] > 1)
		fprintf(verbose_file, "%d shift/reduce conflicts",
			SRconflicts[i]);
	    if (SRconflicts[i] && RRconflicts[i])
		fprintf(verbose_file, ", ");
	    if (RRconflicts[i] == 1)
		fprintf(verbose_file, "1 reduce/reduce conflict");
	    else if (RRconflicts[i] > 1)
		fprintf(verbose_file, "%d reduce/reduce conflicts",
			RRconflicts[i]);
	    fprintf(verbose_file, ".\n");
	}
    }
}
