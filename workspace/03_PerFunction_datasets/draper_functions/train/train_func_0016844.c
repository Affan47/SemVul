ct_tally(int dist, int lc)
{
	G1.l_buf[G2.last_lit++] = lc;
	if (dist == 0) {

		G2.dyn_ltree[lc].Freq++;
	} else {

		dist--;
		Assert((ush) dist < (ush) MAX_DIST
		 && (ush) lc <= (ush) (MAX_MATCH - MIN_MATCH)
		 && (ush) D_CODE(dist) < (ush) D_CODES, "ct_tally: bad match"
		);

		G2.dyn_ltree[G2.length_code[lc] + LITERALS + 1].Freq++;
		G2.dyn_dtree[D_CODE(dist)].Freq++;

		G1.d_buf[G2.last_dist++] = dist;
		G2.flags |= G2.flag_bit;
	}
	G2.flag_bit <<= 1;


	if ((G2.last_lit & 7) == 0) {
		G2.flag_buf[G2.last_flags++] = G2.flags;
		G2.flags = 0;
		G2.flag_bit = 1;
	}

	if ((G2.last_lit & 0xfff) == 0) {

		ulg out_length = G2.last_lit * 8L;
		ulg in_length = (ulg) G1.strstart - G1.block_start;
		int dcode;

		for (dcode = 0; dcode < D_CODES; dcode++) {
			out_length += G2.dyn_dtree[dcode].Freq * (5L + extra_dbits[dcode]);
		}
		out_length >>= 3;
		Trace((stderr,
			   "\nlast_lit %u, last_dist %u, in %ld, out ~%ld(%ld%%) ",
			   G2.last_lit, G2.last_dist, in_length, out_length,
			   100L - out_length * 100L / in_length));
		if (G2.last_dist < G2.last_lit / 2 && out_length < in_length / 2)
			return 1;
	}
	return (G2.last_lit == LIT_BUFSIZE - 1 || G2.last_dist == DIST_BUFSIZE);


}
