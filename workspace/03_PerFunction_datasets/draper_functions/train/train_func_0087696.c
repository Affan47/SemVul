vm_vec_mag_quick(const vms_vector *v)
{
	fix a,b,c,bc;

	a = labs(v->x);
	b = labs(v->y);
	c = labs(v->z);

	if (a < b) {
		fix t=a; a=b; b=t;
	}

	if (b < c) {
		fix t=b; b=c; c=t;

		if (a < b) {
			fix t=a; a=b; b=t;
		}
	}

	bc = (b>>2) + (c>>3);

	return a + bc + (bc>>1);
}
