mpw_div(mpw_ptr rop,mpw_ptr op1, mpw_ptr op2)
{
	if (MPW_IS_REAL (op1) && MPW_IS_REAL (op2)) {
		if G_UNLIKELY (mpwl_zero_p (op2->r)) {
			gel_errorout (_("Division by zero!"));
			gel_error_num=GEL_NUMERICAL_MPW_ERROR;
			return;
		}
		MAKE_REAL(rop);
		if (rop != op1 && rop != op2) {
			MAKE_EMPTY (rop->r, MAX (op1->r->type, op2->r->type));
		} else {
			MAKE_COPY(rop->r);
		}
		mpwl_div(rop->r,op1->r,op2->r);
	} else {
		MpwRealNum t1 = {{NULL}};
		MpwRealNum t2 = {{NULL}};
		MpwRealNum *r1;
		MpwRealNum *i1;
		MpwRealNum *r2;
		MpwRealNum *i2;
		if G_UNLIKELY (mpwl_zero_p (op2->r) && mpwl_zero_p (op2->i)) {
			gel_errorout (_("Division by zero!"));
			gel_error_num=GEL_NUMERICAL_MPW_ERROR;
			return;
		}

		if (rop != op1 && rop != op2) {
			MAKE_EMPTY (rop->r, MAX (op1->r->type, op2->r->type));
			MAKE_EMPTY (rop->i,
				    MAX (MAX (op1->i->type, op2->i->type),
					 rop->r->type));
		} else {
			MAKE_COPY(rop->r);
			MAKE_COPY(rop->i);
		}

		MAKE_CPLX_OPS(op1,r1,i1);
		MAKE_CPLX_OPS(op2,r2,i2);

		mpwl_init_type(&t1,MPW_INTEGER);
		mpwl_init_type(&t2,MPW_INTEGER);


		mpwl_mul(rop->r,r1,r2);
		mpwl_mul(&t1,i1,i2);
		mpwl_add(rop->r,rop->r,&t1);

		mpwl_mul(&t1,r2,r2);
		mpwl_mul(&t2,i2,i2);
		mpwl_add(&t2,&t2,&t1);

		mpwl_div(rop->r,rop->r,&t2);


		mpwl_mul(rop->i,i1,r2);
		mpwl_mul(&t1,r1,i2);
		mpwl_neg(&t1,&t1);
		mpwl_add(rop->i,rop->i,&t1);


		mpwl_div(rop->i,rop->i,&t2);

		mpwl_clear(&t1);
		mpwl_clear(&t2);

		mpw_uncomplex(rop);

		BREAK_CPLX_OPS(op1,r1,i1);
		BREAK_CPLX_OPS(op2,r2,i2);
	}
}
