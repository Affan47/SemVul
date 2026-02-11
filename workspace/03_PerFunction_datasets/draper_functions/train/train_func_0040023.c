mpw_pow_ui(mpw_ptr rop,mpw_ptr op, unsigned long int e)
{
	if (MPW_IS_REAL (op)) {
		MAKE_REAL(rop);
		if (rop != op) {
			MAKE_EMPTY (rop->r, op->r->type);
		} else {
			MAKE_COPY (rop->r);
		}
		mpwl_pow_ui(rop->r,op->r,e,FALSE);
	} else {
		mpw_ln(rop,op);
		mpw_mul_ui(rop,rop,e);
		mpw_exp(rop,rop);
	}
}
