parse_primary(struct parsing *p)
{
	struct expr *e;

	switch (p->token) {
	case EO_NOT: {
		struct expr *res;

		if (lex(p) != 0)
			return NULL;
		e = parse_primary(p);
		if (e == NULL)
			return NULL;
		res = parser_malloc(p, sizeof(*res));
		if (res == NULL)
			goto err_e;
		res->op = EO_NOT;
		res->v.sub[0] = e;
		return res;
	}

	case T_LEFT_PAREN: {
		if (lex(p) != 0)
			return NULL;
		e = parse_or(p);
		if (e == NULL)
			return NULL;
		if (p->token != T_RIGHT_PAREN) {
			if (asprintf(p->error,
				     "Right paren expected, got `%.*s'",
				     p->token_len, p->token_start) < 0)
				*p->error = NULL;
			goto err_e;
		}
		if (lex(p) != 0)
			goto err_e;
		return e;
	}

	case T_FIELD_ESCAPE: case T_STRING:
		return parse_comparison(p);

	default:
		if (asprintf(p->error, "Unexpected token `%.*s'", p->token_len,
			     p->token_start) < 0)
			*p->error = NULL;
		return NULL;
	}
err_e:
	expr_free(e);
	return NULL;
}
