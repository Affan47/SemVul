gnm_owent_T3 (gnm_float h, gnm_float a, int order)
{
	static const gnm_float c2[] = {
		GNM_const(+0.99999999999999987510),
		GNM_const(-0.99999999999988796462),
		GNM_const(+0.99999999998290743652),
		GNM_const(-0.99999999896282500134),
		GNM_const(+0.99999996660459362918),
		GNM_const(-0.99999933986272476760),
		GNM_const(+0.99999125611136965852),
		GNM_const(-0.99991777624463387686),
		GNM_const(+0.99942835555870132569),
		GNM_const(-0.99697311720723000295),
		GNM_const(+0.98751448037275303682),
		GNM_const(-0.95915857980572882813),
		GNM_const(+0.89246305511006708555),
		GNM_const(-0.76893425990463999675),
		GNM_const(+0.58893528468484693250),
		GNM_const(-0.38380345160440256652),
		GNM_const(+0.20317601701045299653),
		GNM_const(-0.82813631607004984866E-01),
		GNM_const(+0.24167984735759576523E-01),
		GNM_const(-0.44676566663971825242E-02),
		GNM_const(+0.39141169402373836468E-03)
	};

	const gnm_float ah = a * h;
	const gnm_float as = a * a;
	const gnm_float y = 1 / (h * h);
	gnm_float vi = a * dnorm (ah, 0, 1, FALSE);
	gnm_float zi = gnm_erf (ah / M_SQRT2gnum) / (2 * h);
	gnm_float val = 0;
	int i;

	g_return_val_if_fail (order < (int)G_N_ELEMENTS(c2), gnm_nan);

	for (i = 0; i <= order; i++) {
		val += zi * c2[i];
		zi = y * ((i + i + 1) * zi - vi);
		vi *= as;
	}
	return val * dnorm (h, 0, 1, FALSE);
}
