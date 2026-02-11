chk_minus (FP___TYPE a, FP___TYPE b, FP___TYPE r)
{

	if (b == QUAD_MIN) {
		if (a >= 0)
			return 1;
		else
			return 0;
	}

	return chk_plus (a, -b, r);
}
