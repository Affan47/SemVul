expr_elements_count(arg_t *arg, asn1p_expr_t *expr) {
	asn1p_expr_t *topmost_parent;
	asn1p_expr_t *v;
	int elements = 0;

	topmost_parent = asn1f_find_terminal_type_ex(arg->asn, expr);
	if(!topmost_parent) return 0;

	if(!(topmost_parent->expr_type & ASN_CONSTR_MASK)
	&& !topmost_parent->expr_type == ASN_BASIC_INTEGER
	&& !topmost_parent->expr_type == ASN_BASIC_ENUMERATED)
		return 0;

	TQ_FOR(v, &(topmost_parent->members), next) {
		if(v->expr_type != A1TC_EXTENSIBLE)
			elements++;
	}

	return elements;
}
