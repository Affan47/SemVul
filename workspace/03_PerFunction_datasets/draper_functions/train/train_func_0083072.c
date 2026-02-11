getmixer(struct cmdif *cif, short num, unsigned short *rval,
	 unsigned short *lval)
{
	union cmdret rptr = CMDRET_ZERO;

	if (SEND_RDGV(cif, num, num, &rptr) && SEND_RDGV(cif, num, num, &rptr))
		return -EIO;
	*rval = rptr.retwords[0];
	*lval = rptr.retwords[1];
	snd_printdd("got mixer %d: 0x%x 0x%x\n", num, *rval, *lval);
	return 0;
}
