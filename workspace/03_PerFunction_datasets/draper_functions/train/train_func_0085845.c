accept_extended_affine(struct isl_stream *s,
	__isl_take isl_space *dim, struct vars *v, int rational)
{
	isl_space *space;
	isl_map *cond;
	isl_pw_aff *pwaff;
	struct isl_token *tok;
	int line = -1, col = -1;
	int is_comp;

	set_current_line_col(s, &line, &col);

	pwaff = accept_affine(s, dim, v);
	if (rational)
		pwaff = isl_pw_aff_set_rational(pwaff);
	if (!pwaff)
		return NULL;

	tok = isl_stream_next_token(s);
	if (!tok)
		return isl_pw_aff_free(pwaff);

	is_comp = is_comparator(tok);
	isl_stream_push_token(s, tok);
	if (!is_comp)
		return pwaff;

	space = isl_pw_aff_get_domain_space(pwaff);
	cond = isl_map_universe(isl_space_unwrap(space));

	if (push_aff(s, line, col, pwaff) < 0)
		return NULL;

	cond = read_formula(s, v, cond, rational);

	return accept_ternary(s, cond, v, rational);
}
