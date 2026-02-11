get_from_to_step_fitz(TOKENS tk, int ntok, int *curtok, double* from, double* to, double* step) throw(ParserError) {
	(*curtok) = (*curtok) + 1;
	if ((*curtok) >= ntok) {
		return;
	}
	if (str_i_equals(tk[(*curtok)], "FROM")) {
		*from = get_next_exp(tk, ntok, curtok);
		(*curtok) = (*curtok) + 1;
	}
	if ((*curtok) >= ntok) {
		return;
	}
	if (str_i_equals(tk[(*curtok)], "TO")) {
		*to = get_next_exp(tk, ntok, curtok);
		(*curtok) = (*curtok) + 1;
	}
	if ((*curtok) >= ntok) {
		return;
	}
	if (str_i_equals(tk[(*curtok)], "STEP")) {
		*step = get_next_exp(tk, ntok, curtok);
		(*curtok) = (*curtok) + 1;
	}
	if ((*curtok) < ntok) {
		stringstream err;
		err << "illegal keyword in range expression '" << tk[(*curtok)] << "'";
		g_throw_parser_error(err.str());
	}
	if (*from >= *to) {
		ostringstream err;
		err << "from value (" << *from << ") should be strictly smaller than to value (" << *to << ") in letz block";
		g_throw_parser_error(err.str());
	}
	if (*step <= 0.0) {
		ostringstream err;
		err << "step value (" << *from << ") should be strictly positive in letz block";
		g_throw_parser_error(err.str());
	}
}
