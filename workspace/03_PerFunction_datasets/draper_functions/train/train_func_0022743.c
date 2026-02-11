entropy_collect_timing(SHA1Context *ctx, bool slow)
{
	double v[4];
	tm_t before, after;

	tm_now_exact(&before);

	v[0] = tm_cputime(&v[1], &v[2]);

	if (slow) {
		compat_sleep_ms(2);
	} else {
		entropy_delay();
	}

	tm_now_exact(&after);
	v[3] = tm_elapsed_f(&after, &before);

	entropy_array_double_collect(ctx, v, G_N_ELEMENTS(v));
}
