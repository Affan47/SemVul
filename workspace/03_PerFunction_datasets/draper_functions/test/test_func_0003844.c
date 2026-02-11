get_contour_values(GLEContourInfo* info, int ct) throw(ParserError) {
	double from, to, step;
	bool has_from = false;
	bool has_to = false;
	bool has_step = false;
	while (ct < ntk) {
		if (str_i_equals(tk[ct+1], "FROM")) {
			ct++;
			from = get_next_exp(tk, ntk, &ct);
			has_from = true;
		} else if (str_i_equals(tk[ct+1], "TO")) {
			ct++;
			to = get_next_exp(tk, ntk, &ct);
			has_to = true;
		} else if (str_i_equals(tk[ct+1], "STEP")) {
			ct++;
			step = get_next_exp(tk, ntk, &ct);
			has_step = true;
		} else {
			double v = get_next_exp(tk, ntk, &ct);
			info->addValue(v);
		}
	}
	if (has_from && has_to && has_step) {
		info->fillDefault(from, to, step);
	}
}
