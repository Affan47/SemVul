K_to_CMY(int nb)


{
	int i;
	Byte *pK = p_K, *pC = p_C, *pM = p_M, *pY = p_Y;

	for (i = 0; i < nb; i++, pK++) {
		*pC++ |= *pK;
		*pM++ |= *pK;
		*pY++ |= *pK;
	}
}
