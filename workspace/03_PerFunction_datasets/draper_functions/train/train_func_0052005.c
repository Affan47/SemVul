resample_1_s32_to_1_s32 (xmms_sample_converter_t *conv, xmms_sample_t *tbuf, guint len, xmms_sample_t *tout)
{
	xmms_samples32_t *buf = (xmms_samples32_t *) tbuf;
	xmms_samples32_t *outbuf = (xmms_samples32_t *) tout;
	xmms_samples32_t *out;
	guint pos, ipos;
	gint i, n=0;

	pos = conv->offset;

	while (pos < len * conv->interpolator_ratio) {
		guint32 temp[1];
		xmms_samples32_t *buf1, *buf2;
		gfloat bfrac = ((gfloat) (pos % (conv->interpolator_ratio))) / (conv->interpolator_ratio);
		gfloat afrac = 1.0 - bfrac;

		ipos = pos / conv->interpolator_ratio;

		if (ipos < 1) {
			buf1 = (xmms_samples32_t *)conv->state;
		} else {
			buf1 = &buf[1 * (ipos - 1)];
		}
		buf2 = &buf[1 * ipos];


		for (i = 0; i < 1; i++) {
			temp[i] = afrac * READs32 (buf1[i]) + bfrac * READs32 (buf2[i]);
		}

		out = &outbuf[1 * n];

		out[0] = WRITEs32(temp[0]);


		n++;
		pos += conv->decimator_ratio;
	}

	conv->offset = pos - len * conv->interpolator_ratio;

	for (i = 0; i < 1; i++) {
		((xmms_samples32_t *)conv->state)[i] = buf[1*(len-1) + i];
	}
	return n;
}
