read_tuple_var_list(struct isl_stream *s,
	struct vars *v, int rational, int comma)
{
	int i = 0;
	struct isl_token *tok;
	isl_multi_pw_aff *res;

	res = tuple_alloc(v);

	if (isl_stream_next_token_is(s, ']'))
		return res;

	while ((tok = next_token(s)) != NULL) {
		int new_name = 0;

		res = tuple_add_dim(res, v);

		if (tok->type == ISL_TOKEN_IDENT) {
			int n = v->n;
			int p = vars_pos(v, tok->u.s, -1);
			if (p < 0)
				goto error;
			new_name = p >= n;
		}

		if (new_name) {
			res = tuple_set_dim_name(res, i, v->v->name);
			isl_token_free(tok);
			if (isl_stream_eat_if_available(s, '='))
				res = read_tuple_var_def(s, res, i, v,
							rational);
		} else {
			isl_stream_push_token(s, tok);
			tok = NULL;
			if (vars_add_anon(v) < 0)
				goto error;
			res = read_tuple_var_def(s, res, i, v, rational);
		}

		tok = isl_stream_next_token(s);
		if (!comma && tok && tok->type == ']' &&
		    isl_stream_next_token_is(s, '[')) {
			isl_token_free(tok);
			tok = isl_stream_next_token(s);
		} else if (!tok || tok->type != ',')
			break;

		isl_token_free(tok);
		i++;
	}
	if (tok)
		isl_stream_push_token(s, tok);

	return res;
error:
	isl_token_free(tok);
	return isl_multi_pw_aff_free(res);
}
