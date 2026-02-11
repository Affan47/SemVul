hkl_lattice_get_1_B(const HklLattice *self, HklMatrix *B)
{
	HklMatrix tmp;
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;

	if(!self || !B)
		return HKL_FAIL;


	hkl_lattice_get_B(self, &tmp);


	a = tmp.data[0][0];
	b = tmp.data[0][1];
	c = tmp.data[0][2];
	d = tmp.data[1][1];
	e = tmp.data[1][2];
	f = tmp.data[2][2];

	B->data[0][0] = 1 / a;
	B->data[0][1] = -b / a / d;
	B->data[0][2] = (b * e - d * c) / a / d / f;

	B->data[1][0] = 0;
	B->data[1][1] = 1 / d;
	B->data[1][2] = -e / d / f;

	B->data[2][0] = 0;
	B->data[2][1] = 0;
	B->data[2][2] = 1 / f;

	return HKL_SUCCESS;
}
