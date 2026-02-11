decodePageChop(const fxStr& pph, const Class2Params& params)
{
    if (params.ln == LN_INF && pph.length() >= 2+5+1 && pph[2] == 'Z') {
	char buf[5];
	buf[0] = pph[2+1];
	buf[1] = pph[2+2];
	buf[2] = pph[2+3];
	buf[3] = pph[2+4];
	buf[4] = '\0';
	return ((u_int) strtoul(buf, NULL, 16));
    } else
	return (0);
}
