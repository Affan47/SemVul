sa_report_all(FILE *fd)
{
	struct sa      *sa;
	int             i;

	for (i = 0; i <= bucket_mask; i++)
		for (sa = LIST_FIRST(&sa_tab[i]); sa; sa = LIST_NEXT(sa, link))
			if (sa->phase == 1)
				fprintf(fd, "SA name: none (phase 1)\n\n");
			else
				sa_dump_all(fd, sa);
}
