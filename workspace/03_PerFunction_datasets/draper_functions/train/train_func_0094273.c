point_add(const curve_point *cp1, curve_point *cp2)
{
	int i;
	uint32_t temp;
	bignum256 lambda, inv, xr, yr;

	if (point_is_infinity(cp1)) {
		return;
	}
	if (point_is_infinity(cp2)) {
		point_copy(cp1, cp2);
		return;
	}
	if (point_is_equal(cp1, cp2)) {
		point_double(cp2);
		return;
	}
	if (point_is_negative_of(cp1, cp2)) {
		point_set_infinity(cp2);
		return;
	}

	bn_subtractmod(&(cp2->x), &(cp1->x), &inv, &prime256k1);
	bn_inverse(&inv, &prime256k1);
	bn_subtractmod(&(cp2->y), &(cp1->y), &lambda, &prime256k1);
	bn_multiply(&inv, &lambda, &prime256k1);


	xr = lambda;
	bn_multiply(&xr, &xr, &prime256k1);
	temp = 1;
	for (i = 0; i < 9; i++) {
		temp += 0x3FFFFFFF + xr.val[i] + 2u * prime256k1.val[i] - cp1->x.val[i] - cp2->x.val[i];
		xr.val[i] = temp & 0x3FFFFFFF;
		temp >>= 30;
	}
	bn_fast_mod(&xr, &prime256k1);
	bn_mod(&xr, &prime256k1);


	bn_subtractmod(&(cp1->x), &xr, &yr, &prime256k1);
	bn_multiply(&lambda, &yr, &prime256k1);
	bn_subtractmod(&yr, &(cp1->y), &yr, &prime256k1);
	bn_fast_mod(&yr, &prime256k1);
	bn_mod(&yr, &prime256k1);

	cp2->x = xr;
	cp2->y = yr;
}
