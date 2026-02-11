gf128mul_4k_lle(be128 *a, struct gf128mul_4k *t)
{
	u8 *ap = (u8 *)a;
	be128 r[1];
	int i = 15;

	*r = t->t[ap[15]];
	while (i--) {
		gf128mul_x8_lle(r);
		be128_xor(r, r, &t->t[ap[i]]);
	}
	*a = *r;
}
