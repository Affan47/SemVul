do_scale(int& ct) {
	if (str_i_equals(tk[ct+1], "AUTO")) {
		g_auto_s_v = true;
		g_auto_s_h = true;
		ct++;
	} else {
		g_hscale = next_exp;
		g_vscale = next_exp;
	}
	do_remaining_entries(ct+1, false);
}
