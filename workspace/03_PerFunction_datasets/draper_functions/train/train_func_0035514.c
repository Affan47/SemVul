ao_tail(OPT *aod, int *tailc, char ***tailv)
{
	int		ret = LAMERROR;

	if (aod) {
		*tailc = aod->ao_tailc;
		*tailv = aod->ao_tailv;
		ret = 0;
	}

	return(ret);
}
