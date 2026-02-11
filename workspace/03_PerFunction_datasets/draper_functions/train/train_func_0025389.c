pageline(time_t deltasec, time_t deltatic, time_t hz,
				int ncpu, struct osrel *osr, char *tstamp)
{
	double		si, so, pi, po, fo;
	struct genstat	*scur, *spre;
	struct tabstat	*pcur, *ppre;


	if ( !getcset("genstat", (void **)&scur, (void **)&spre) )
			return(0);

	pi = subtract(scur->pgpgin,  spre->pgpgin);
	po = subtract(scur->pgpgout, spre->pgpgout);
	si = subtract(scur->pswpin,  spre->pswpin);
	so = subtract(scur->pswpout, spre->pswpout);

	if (getcset("tabstat", (void **)&pcur, (void **)&ppre) )
		fo = subtract(pcur->totforks, ppre->totforks);
	else
		fo = 0;

	printf("%9.2lf %9.2lf    %9.2lf %9.2lf        %7.2lf\n",
		pi / deltasec,
		po / deltasec,
		si / deltasec,
		so / deltasec,
		fo / deltasec);

	return(1);
}
