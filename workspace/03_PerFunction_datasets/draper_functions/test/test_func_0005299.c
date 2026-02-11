zeros()
{
	if (skip() == 1) {
		double* p = base();
		for (int i = 0; i < length()/ZeroPad::length;
			 i++, p += ZeroPad::length)
			memcpy(p, zero_pad.getBase(), sizeof(double)*ZeroPad::length);
		for ( ; p < base()+length(); p++)
			*p = 0.0;
	} else {
		for (int i = 0; i < length(); i++)
			operator[](i) = 0.0;
	}
}
