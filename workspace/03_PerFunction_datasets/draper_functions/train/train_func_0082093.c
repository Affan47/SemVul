mpw_abs(mpw_ptr rop,mpw_ptr op)
{
	if (MPW_IS_REAL (op)) {
		if(mpwl_sgn(op->r)<0)
			mpw_neg(rop,op);
		else
			mpw_set(rop,op);
	} else {
		MpwRealNum t = {{NULL}};

		if (rop != op) {
			MAKE_EMPTY(rop->r, op->r->type);
		} else {
			MAKE_COPY (rop->r);
		}

		mpwl_init_type (&t, op->i->type);

		mpwl_mul(rop->r,op->r,op->r);
		mpwl_mul(&t,op->i,op->i);
		mpwl_add(rop->r,rop->r,&t);

		mpwl_clear(&t);

		mpwl_sqrt(rop->r,rop->r);

		MAKE_REAL (rop);
	}
}
