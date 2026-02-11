trimExcessScale(guint64* pclo, guint64* pchi, int* pScale)
{
	guint64 ilo = *pclo, lastlo;
	guint64 ihi = *pchi, lasthi;
	int scale = *pScale;
	int i = 0, roundBit;

	while (scale > 0) {
		scale--;
		i++;
		lastlo = ilo;
		lasthi = ihi;

		roundBit = div128by32(&ilo, &ihi, 10, &rest);
		if (rest != 0){
			i--;
			if (i == 0)
				return;

			*pclo = lastlo;
			*pchi = lasthi;
			*pScale = scale+1;
			return;
		}
	}
}
