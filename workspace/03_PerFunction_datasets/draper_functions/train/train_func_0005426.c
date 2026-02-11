nextStream ()
    {
	MatVecModM (A1p127, Ig, m1);
	MatVecModM (A2p127, &Ig[3], m2);
	for (int i = 0; i < 6; ++i) {
	    Bg[i] = Ig[i];
	}
    }
