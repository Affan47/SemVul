bestx (unsigned stm, dtm_t a, dtm_t b)
{
	unsigned int key;
	static const unsigned int
	comparison [4] [4] = {

	 {0, 3, 0, 0},
	 {0, 1, 0, 0},
	 {3, 3, 2, 0},
	 {3, 3, 3, 0}


	};

	static const unsigned int xorkey [2] = {0, 3};
	dtm_t retu[4];
	dtm_t ret = iFORBID;

	assert (stm == WH || stm == BL);
	assert ((a & iUNKNBIT) == 0 && (b & iUNKNBIT) == 0 );

	if (a == iFORBID)
		return b;
	if (b == iFORBID)
		return a;

	retu[0] = a;
	retu[1] = a;
	retu[2] = b;
	retu[3]	= b;
	if (b < a) {
		retu[1] = b;
		retu[2] = a;
	}

	key = comparison [a&3] [b&3] ^ xorkey[stm];
	ret = retu [key];

	return ret;
}
