xsp2cie_apply(xsp2cie *p,
xspect *out,
xspect *in
) {
	int j;

	if (p->media.spec_n == 0)
		return 1;

	if (p->media.spec_n != in->spec_n
	 || p->media.spec_wl_short != in->spec_wl_short
	 || p->media.spec_wl_long != in->spec_wl_long)
		return 1;

	*out = *in;


	for (j = 0; j < p->media.spec_n; j++) {
		if (p->media.spec[j] < 0.01)
			out->spec[j] = in->spec[j] * 0.01;
		else
			out->spec[j] = in->spec[j] * p->media.spec[j];
	}

	out->norm = in->norm * p->media.norm;
	return 0;
}
