tda10021_set_symbolrate (struct tda10021_state* state, u32 symbolrate)
{
	s32 BDR;
	s32 BDRI;
	s16 SFIL=0;
	u16 NDEC = 0;
	u32 tmp, ratio;

	if (symbolrate > XIN/2)
		symbolrate = XIN/2;
	if (symbolrate < 500000)
		symbolrate = 500000;

	if (symbolrate < XIN/16) NDEC = 1;
	if (symbolrate < XIN/32) NDEC = 2;
	if (symbolrate < XIN/64) NDEC = 3;

	if (symbolrate < (u32)(XIN/12.3)) SFIL = 1;
	if (symbolrate < (u32)(XIN/16))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/24.6)) SFIL = 1;
	if (symbolrate < (u32)(XIN/32))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/49.2)) SFIL = 1;
	if (symbolrate < (u32)(XIN/64))	 SFIL = 0;
	if (symbolrate < (u32)(XIN/98.4)) SFIL = 1;

	symbolrate <<= NDEC;
	ratio = (symbolrate << 4) / FIN;
	tmp =  ((symbolrate << 4) % FIN) << 8;
	ratio = (ratio << 8) + tmp / FIN;
	tmp = (tmp % FIN) << 8;
	ratio = (ratio << 8) + DIV_ROUND_CLOSEST(tmp, FIN);

	BDR = ratio;
	BDRI = (((XIN << 5) / symbolrate) + 1) / 2;

	if (BDRI > 0xFF)
		BDRI = 0xFF;

	SFIL = (SFIL << 4) | tda10021_inittab[0x0E];

	NDEC = (NDEC << 6) | tda10021_inittab[0x03];

	_tda10021_writereg (state, 0x03, NDEC);
	_tda10021_writereg (state, 0x0a, BDR&0xff);
	_tda10021_writereg (state, 0x0b, (BDR>> 8)&0xff);
	_tda10021_writereg (state, 0x0c, (BDR>>16)&0x3f);

	_tda10021_writereg (state, 0x0d, BDRI);
	_tda10021_writereg (state, 0x0e, SFIL);

	return 0;
}
