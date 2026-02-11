asn1c_recurse(arg_t *arg, asn1p_expr_t *expr, int (*callback)(arg_t *arg, void *key), void *key) {
	arg_t tmp = *arg;
	int maxret = 0;
	int ret;

	if(expr->_mark) return 0;
	expr->_mark |= TM_RECURSION;


	tmp.expr = expr;
	maxret = callback(&tmp, key);
	if(maxret <= 1) {


		TQ_FOR(tmp.expr, &(expr->members), next) {
			ret = asn1c_recurse(&tmp, tmp.expr, callback, key);
			if(ret > maxret)
				maxret = ret;
			if(maxret > 1) break;
		}
	}

	expr->_mark &= ~TM_RECURSION;
	return maxret;
}
