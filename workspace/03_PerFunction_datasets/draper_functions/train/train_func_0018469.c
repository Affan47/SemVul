apply_s32 (void *buf, gint len, gfloat gain)
{
	xmms_samples32_t *samples = (xmms_samples32_t *) buf;
	gint i;

	for (i = 0; i < len; i++) {
		gdouble sample = samples[i] * gain;
		samples[i] = CLAMP (sample, XMMS_SAMPLES32_MIN,
		                    XMMS_SAMPLES32_MAX);
	}
}
