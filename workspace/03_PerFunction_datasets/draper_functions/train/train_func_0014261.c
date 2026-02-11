asn1f_fix_bit_string_value(arg_t *arg, asn1p_expr_t *ttype) {
	asn1p_expr_t *expr = arg->expr;
	int r_value = 0;

	DEBUG("(%s) for line %d",
		expr->Identifier, expr->_lineno);

	switch(expr->value->type) {
	case ATV_UNPARSED:


		if(asn1f_BS_unparsed_convert(arg, expr->value, ttype)) {
			r_value = -1;
			break;
		}

	case ATV_BITVECTOR:
		asn1f_BS_remove_trailing_zero_bits(expr->value);
		break;
	default:
		break;
	}

	return r_value;
}
