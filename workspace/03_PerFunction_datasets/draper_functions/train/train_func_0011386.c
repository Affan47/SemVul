main(int argc, char **argv)
{
double n;
struct cthreadinfo *cit;
int	i, j;

	if (argc < 2)	return (1);

	j=atoi(argv[1]);
	if (argc > 2)
		ndelay=atoi(argv[2]);

	if (j <= 0 || j > sizeof(buf)/sizeof(buf[0]))	return (1);

	if ( (cit=cthread_init(2, sizeof(double), workfunc, cleanupfunc)) == 0)
	{
		perror("cthread_init");
		return (1);
	}

	for (i=0; i<j; i++)
	{
		n= i+1;

		if (cthread_go(cit, getwork, &n))
		{
			perror("cthread_go");
			return (1);
		}
		printf ("Started %d\n", i+1);
	}
	cthread_wait(cit);

	qsort(buf, bufcnt, sizeof(buf[0]), &cmpdbl);

	for (i=0; i<bufcnt; i++)
	{
		printf("%6.2f\n", buf[i]);
	}
	return (0);
}
