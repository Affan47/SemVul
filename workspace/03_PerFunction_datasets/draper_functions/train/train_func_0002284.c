gaussian_psf(struct psf *psf, double ovs, double s)
{
	int xi, yi;
	double rs, v, vol = 0.0;

	s *= ovs;
	d3_printf("gauss_psf: s=%.3f\n", s);

	for (xi = 0; xi < psf->w; xi ++)
		for (yi = 0; yi < psf->h; yi++) {
			rs = sqr(xi - psf->cx - psf->dx) + sqr(yi - psf->cy - psf->dy);
			v = exp( - rs / 2 / sqr(s));
			vol += v;
			psf->d[xi][yi] = v;
		}
	return vol;
}
