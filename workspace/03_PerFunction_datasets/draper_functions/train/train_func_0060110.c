zmul(ZVALUE z1, ZVALUE z2, ZVALUE *res)
{
	LEN len;

	if (ziszero(z1) || ziszero(z2)) {
		*res = _zero_;
		return;
	}
	if (zisunit(z1)) {
		zcopy(z2, res);
		res->sign = (z1.sign != z2.sign);
		return;
	}
	if (zisunit(z2)) {
		zcopy(z1, res);
		res->sign = (z1.sign != z2.sign);
		return;
	}


	len = z1.len;
	if (len < z2.len)
		len = z2.len;
	len = 2 * len + 64;
	tempbuf = zalloctemp(len);

	res->sign = (z1.sign != z2.sign);
	res->v = alloc(z1.len + z2.len + 2);
	res->len = domul(z1.v, z1.len, z2.v, z2.len, res->v);
}
