findconst(register long m)
#endif
{
	register struct Literal *litp, *litpe;

	litp = litpool;
	for(litpe = litp + nliterals; litp < litpe; litp++)
		if (litp->litnum ==  m)
			return litp->cds[0];
	Fatal("findconst failure!");
	return 0;
	}
