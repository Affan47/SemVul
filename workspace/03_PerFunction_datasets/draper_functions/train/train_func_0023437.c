dowhatdoes()
{
	char bufr[BUFSZ];
	char q, *reslt;

#if defined(UNIX) || defined(VMS)
	introff();
#endif
	q = yn_function("What command?", (char *)0, '\0');
#if defined(UNIX) || defined(VMS)
	intron();
#endif
	reslt = dowhatdoes_core(q, bufr);
	if (reslt)
		pline("%s", reslt);
	else
		pline("I've never heard of such commands.");
	return 0;
}
