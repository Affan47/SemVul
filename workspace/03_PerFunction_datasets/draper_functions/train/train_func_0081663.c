snd_rme96_getinputtype(struct rme96 *rme96)
{
	if (rme96->areg & RME96_AR_ANALOG) {
		return RME96_INPUT_ANALOG;
	}
	return ((rme96->wcreg >> RME96_WCR_BITPOS_INP_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_INP_1) & 1) << 1);
}
