generate_sine8_2(const char *fn, const double sample_rate, const unsigned samples, const double f1, const double a1, const double f2, const double a2, double fmult)
{
	const FLAC__int8 full_scale = 127;
	const double delta1 = 2.0 * M_PI / ( sample_rate / f1);
	const double delta2 = 2.0 * M_PI / ( sample_rate / f2);
	FILE *f;
	double theta1, theta2;
	unsigned i;

	if(0 == (f = flac_fopen(fn, "wb")))
		return false;

	for(i = 0, theta1 = theta2 = 0.0; i < samples; i++, theta1 += delta1, theta2 += delta2) {
		double val = (a1*sin(theta1) + a2*sin(theta2))*(double)full_scale;
		FLAC__int8 v = (FLAC__int8)(val + 0.5);
		if(fwrite(&v, sizeof(v), 1, f) < 1)
			goto foo;
		val = -(a1*sin(theta1*fmult) + a2*sin(theta2*fmult))*(double)full_scale;
		v = (FLAC__int8)(val + 0.5);
		if(fwrite(&v, sizeof(v), 1, f) < 1)
			goto foo;
	}

	fclose(f);
	return true;
foo:
	fclose(f);
	return false;
}
