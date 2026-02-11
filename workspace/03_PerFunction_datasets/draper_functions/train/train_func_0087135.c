pcm_recode(const char *in, int ibps, int ich, char *out, int obps, int och)
{
	int l, r;

	if (ibps == 8) {
		if (ich == 1)
			l = r = in[0];
		else {
			l = in[0];
			r = in[1];
		}

		l *= 256;
		r *= 256;
	} else {
		if (ich == 1)
			l = r = ((short int*) in)[0];
		else {
			l = ((short int*) in)[0];
			r = ((short int*) in)[1];
		}
	}

	if (obps == 8) {
		if (och == 1)
			out[0] = (l + r) / 512;
		else {
			out[0] = l / 256;
			out[1] = r / 256;
		}
	} else {
		if (och == 1)
			((short int*) out)[0] = (l + r) / 2;
		else {
			((short int*) out)[0] = l;
			((short int*) out)[1] = r;
		}
	}
}
