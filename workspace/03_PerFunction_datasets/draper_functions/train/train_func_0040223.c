preparestr(rins, vins)
int rins, vins;
{
	int rw, vw;

	if (overflow(vlen(inputbuf, inputlen) + vins)) return(-1);

	if (!overwritemode) {
		insertchar(rptr, vptr, vins);
		insertbuf(rins);
		insshift(rptr, rins);
		inputlen += rins;
		return(0);
	}

	if (rptr >= inputlen) rw = vw = 0;
	else getcharwidth(inputbuf, rptr, &rw, &vw);

	if (!vw) ;
	else if (vins > vw) insertchar(rptr, vptr, vins - vw);
	else if (vins < vw) deletechar(rptr, vptr, vw - vins);

	if (!rw) ;
	else if (rins > rw) {
		insertbuf(rins - rw);
		insshift(rptr, rins - rw);
	}
	else if (rins < rw) delshift(rptr, rw - rins);

	inputlen += rins - rw;

	return(0);
}
