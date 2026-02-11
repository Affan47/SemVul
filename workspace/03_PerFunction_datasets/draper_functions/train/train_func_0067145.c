dobanner(struct spq *jp)
{
	if  (!(in_params.pi_flags & PI_FORCEHDR)  &&
	     (in_params.pi_flags & PI_NOHDR || jp->spq_jflags & SPQ_NOH))
		return;

	if  (pfile < 0  &&  !opendev())
		seterrorstate((const char *) 0);
	pflush();

	if  (in_params.pi_flags & PI_BANNBAUD)  {
#ifdef	HAVE_TERMIO_H
#ifdef	PRIME
		ioctl(pfile, oTCSETAW, &in_params.pi_banntty);
#else
		ioctl(pfile, TCSETAW, &in_params.pi_banntty);
#endif
#else
		ioctl(pfile, TIOCSETP, &in_params.pi_banntty);
#endif
	}

	if  (!execorsend("BANNDS", bdsstr, in_params.pi_bdocstart, in_params.pi_flags & PI_EX_BDOCST, 0))
		goto  bfin;


	if  (bannprog)  {
		pflush();
		runbann(jp);
	}
	else  if  (filternam)  {
		filtopen();
		bannprin(jp, fpush);
		filtclose(FC_NOERR);
	}
	else  {
		int	lincnt = bannprin(jp, pchar);
		if  (!bdestr)
			pagethrow(lincnt);
	}

	execorsend("BANNDE", bdestr, in_params.pi_bdocend, in_params.pi_flags & PI_EX_BDOCEND, 0);

 bfin:
	pflush();
	Pages_done++;

	if  (in_params.pi_flags & PI_BANNBAUD)  {
#ifdef	HAVE_TERMIO_H
#ifdef	PRIME
		ioctl(pfile, oTCSETAW, &in_params.pi_tty);
#else
		ioctl(pfile, TCSETAW, &in_params.pi_tty);
#endif
#else
		ioctl(pfile, TIOCSETP, &in_params.pi_tty);
#endif
	}
}
