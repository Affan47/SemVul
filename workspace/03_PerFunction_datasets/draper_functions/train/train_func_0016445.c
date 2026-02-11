linear_x_shear(struct ccd_frame *in, struct ccd_frame *out, double a, double c)
{
	int wi, hi, wo, ho;
	float *dpi, *dpo;
	int plane_iter = 0;

	double dwi;

	double xl;
	double xl0;

	int ui, vi;
	double x;
	double ox;
	double v;

	float filler;


	wi = in->w;
	hi = in->h;
	wo = out->w;
	ho = out->h;
	dwi = 1.0 * wi;

	if (!in->stats.statsok)
		frame_stats(in);
	filler = in->stats.cavg;


	if (c < 0) {
		err_printf("linear_x_shear: frame needs 'x' flipping\n");
		return -1;
	}


	while ((plane_iter = color_plane_iter(in, plane_iter))) {
		for (vi = 0; vi < ho; vi++) {
			dpo = get_color_plane(out, plane_iter);
			dpi = get_color_plane(in, plane_iter);
			dpo += wo * vi;
			dpi += wi * vi;
			ox = - a * c * 1.0 * vi;
			x = ox - c;
			xl = c;


			for (ui = 0; ui < wo; ui++) {
				xl = c;
				x += xl;
				if ((x <= 0) || (x > dwi - xl) || (vi >= hi)) {
					*dpo++ = filler;
					continue;
 				}
				xl0 = ceil(x) - x;
				if (xl0 > xl) {
					*dpo++ = *dpi * xl;
					continue;
				}
				v = (*dpi++) * xl0;

				xl -= xl0;
				while (xl > 1.0) {
					v += (*dpi++);

					xl -= 1.0;
				}
				v += (*dpi) * xl;
				*dpo ++ = v;
			}

		}
	}

	return 0;
}
