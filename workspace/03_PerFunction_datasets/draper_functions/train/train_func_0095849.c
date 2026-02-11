tweak_weights(gammapweights out[14], int dst_cmymap, int rel_oride)  {
	int i;

	for (i = 0; i < 14; i++) {
		if (((dst_cmymap & 0x1) && (out[i].ch & gmc_cyan))
		 || ((dst_cmymap & 0x2) && (out[i].ch & gmc_magenta))
		 || ((dst_cmymap & 0x4) && (out[i].ch & gmc_yellow))) {

			out[i].c.w.l = 1.0;
			out[i].c.w.c = 1.0;
			out[i].c.w.h = 1.0;
			out[i].c.cx = 1.0;
		}

		if (rel_oride == 1) {
			out[i].r.rdl = 1.0;
			out[i].r.rdh = 1.0;
			out[i].d.co = 0.0;
			out[i].d.xo = 0.0;

		} else if (rel_oride == 2) {
			out[i].r.rdl *= 1.6;
			out[i].r.rdh *= 1.6;
		}
	}
}
