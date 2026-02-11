scalar_float_op(eval_scalar *xr, const eval_scalar *xa, const eval_scalar *xb, int op)
{
	eval_float ai, bi;
	float a, b, r;
	scalar_context_float(xa, &ai);
	scalar_context_float(xb, &bi);

	a = ai.value;
	b = bi.value;
	switch (op) {
		case '*': r = a*b; break;
		case '/': {
		    if (!b) {
			    set_eval_error("division by zero");
			    return 0;
		    }
		    r = a/b;
		    break;
		}
		case '+': r = a+b; break;
		case '-': r = a-b; break;
		case EVAL_POW: r = pow(a,b); break;
		default: {
			uint64 ri;
			switch (op) {
				case EVAL_EQ: ri = a==b; break;
				case EVAL_NE: ri = a!=b; break;
				case EVAL_GT: ri = a>b; break;
				case EVAL_GE: ri = a>=b; break;
				case EVAL_LT: ri = a<b; break;
				case EVAL_LE: ri = a<=b; break;
				case EVAL_LAND: ri = a && b; break;
				case EVAL_LXOR: ri = !a != !b; break;
				case EVAL_LOR: ri = a || b ; break;
				default:
					set_eval_error("invalid operator");
					return 0;
			}
			xr->type = SCALAR_INT;
			xr->scalar.integer.value = ri;
			xr->scalar.integer.type = TYPE_UNKNOWN;
			return 1;
		}
	}
	xr->type = SCALAR_FLOAT;
	xr->scalar.floatnum.value = r;
	return 1;
}
