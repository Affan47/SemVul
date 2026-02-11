get_out_scale(rspl *s) {

	if (s->g.fminmax_valid == 0)
		get_out_range(s, NULL, NULL);

	return s->g.fscale;
}
