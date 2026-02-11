PreMDCT(int *buf0, int num, const int *csptr)
{
	int i;
	int tr1, ti1, tr2, ti2;
	int cosa, sina, cosb, sinb;
	int *buf1;

	buf1 = buf0 + num - 1;

	for(i = num >> 2; i != 0; i--)
	{
		cosa = *csptr++;
		sina = *csptr++;
		cosb = *csptr++;
		sinb = *csptr++;

		tr1 = *(buf0 + 0);
		ti2 = *(buf0 + 1);
		tr2 = *(buf1 - 1);
		ti1 = *(buf1 + 0);

		*buf0++ = MULHIGH(cosa, tr1) + MULHIGH(sina, ti1);
		*buf0++ = MULHIGH(cosa, ti1) - MULHIGH(sina, tr1);

		*buf1-- = MULHIGH(cosb, ti2) - MULHIGH(sinb, tr2);
		*buf1-- = MULHIGH(cosb, tr2) + MULHIGH(sinb, ti2);
	}
}
