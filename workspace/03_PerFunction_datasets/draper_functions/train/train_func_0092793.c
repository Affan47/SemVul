zminmod(ZVALUE z1, ZVALUE z2, ZVALUE *res)
{
	ZVALUE tmp1, tmp2;
	int sign;
	int cv;

	if (ziszero(z2) || zisneg(z2)) {
		math_error("Mod of non-positive integer");

	}
	if (ziszero(z1) || zisunit(z2)) {
		*res = _zero_;
		return;
	}
	if (zistwo(z2)) {
		if (zisodd(z1))
			*res = _one_;
		else
			*res = _zero_;
		return;
	}


	if (z1.len < z2.len - 1) {
		zcopy(z1, res);
		return;
	}


	sign = z1.sign;
	z1.sign = 0;
	cv = zrel(z1, z2);
	if (cv == 0) {
		*res = _zero_;
		return;
	}
	tmp1 = z1;
	if (cv > 0) {
		z1.sign = (BOOL)sign;
		zmod(z1, z2, &tmp1, 0);
		if (tmp1.len < z2.len - 1) {
			*res = tmp1;
			return;
		}
		sign = 0;
	}


	zsub(z2, tmp1, &tmp2);
	cv = zrel(tmp1, tmp2);
	if (cv < 0) {
		zfree(tmp2);
		tmp1.sign = (BOOL)sign;
		if (tmp1.v == z1.v)
			zcopy(tmp1, res);
		else
			*res = tmp1;
	} else {
		if (cv)
			tmp2.sign = !sign;
		if (tmp1.v != z1.v)
			zfree(tmp1);
		*res = tmp2;
	}
}
