gdither_innner_loop(const GDitherType dt,
    const uint32_t stride, const float bias, const float scale,

    const uint32_t post_scale, const int bit_depth,
    const uint32_t channel, const uint32_t length, float *ts,

    GDitherShapedState *ss, float *x, void *y, const int clamp_u,

    const int clamp_l)
{
    uint32_t pos, i;
    uint8_t *o8 = (uint8_t*) y;
    int16_t *o16 = (int16_t*) y;
    int32_t *o32 = (int32_t*) y;
    float tmp, r, ideal;
    int64_t clamped;

    i = channel;
    for (pos = 0; pos < length; pos++, i += stride) {
	tmp = x[i] * scale + bias;

	switch (dt) {
	case GDitherNone:
	    break;
	case GDitherRect:
	    tmp -= GDITHER_NOISE;
	    break;
	case GDitherTri:
	    r = GDITHER_NOISE - 0.5f;
	    tmp -= r - ts[channel];
	    ts[channel] = r;
	    break;
	case GDitherShaped:

	    ideal = tmp;


	    ss->buffer[ss->phase] = GDITHER_NOISE * 0.5f;
	    tmp += ss->buffer[ss->phase] * shaped_bs[0]
		   + ss->buffer[(ss->phase - 1) & GDITHER_SH_BUF_MASK]
		     * shaped_bs[1]
		   + ss->buffer[(ss->phase - 2) & GDITHER_SH_BUF_MASK]
		     * shaped_bs[2]
		   + ss->buffer[(ss->phase - 3) & GDITHER_SH_BUF_MASK]
		     * shaped_bs[3]
		   + ss->buffer[(ss->phase - 4) & GDITHER_SH_BUF_MASK]
		     * shaped_bs[4];


	    ss->phase = (ss->phase + 1) & GDITHER_SH_BUF_MASK;
	    ss->buffer[ss->phase] = (float)lrintf(tmp) - ideal;
	    break;
	}

	clamped = lrintf(tmp);
	if (clamped > clamp_u) {
		clamped = clamp_u;
	} else if (clamped < clamp_l) {
		clamped = clamp_l;
	}

	switch (bit_depth) {
	case GDither8bit:
	    o8[i] = (u_int8_t) (clamped * post_scale);
	    break;
	case GDither16bit:
	    o16[i] = (int16_t) (clamped * post_scale);
	    break;
	case GDither32bit:
	    o32[i] = (int32_t) (clamped * post_scale);
	    break;
	}
    }
}
