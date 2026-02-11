gf128mul_4k_bbe(be128 *a, struct gf128mul_4k *t)
{
	u8 *ap = (u8 *)a;
	be128 r[1];
	int i = 0;

	*r = t->t[ap[0]];
	while (++i < 16) {
		gf128mul_x8_bbe(r);
		be128_xor(r, r, &t->t[ap[i]]);
	}
	*a = *r;
}
