mpwl_mul(MpwRealNum *rop,MpwRealNum *op1,MpwRealNum *op2)
{
	int t;
	MpwRealNum r = {{NULL}};
	MpwRealNum *rp = NULL;


	if (op1->type == op2->type) {
		if (rop->type != op1->type) {
			mpwl_clear (rop);
			mpwl_init_type (rop, op1->type);
		}
		switch(op1->type) {
		case MPW_FLOAT:
			mpfr_mul (rop->data.fval,
				  op1->data.fval, op2->data.fval,
				  GMP_RNDN);
			break;
		case MPW_RATIONAL:
			mpq_mul(rop->data.rval,op1->data.rval,op2->data.rval);
			mpwl_make_int(rop);
			break;
		case MPW_INTEGER:
			mpz_mul(rop->data.ival,op1->data.ival,op2->data.ival);
			break;
		}
		return;
	}

	t = MPWL_MAX_TYPE (op1, op2);
	if (rop != op1 && rop != op2 && rop->type == t) {
		rp = rop;
	} else {
		mpwl_init_type (&r, t);
		rp = &r;
	}

	switch (t) {
	case MPW_FLOAT:
		if (op1->type == MPW_FLOAT) {
			switch(op2->type) {
			case MPW_RATIONAL:
				mpfr_mul_q (rp->data.fval, op1->data.fval,
					    op2->data.rval, GMP_RNDN);
				break;
			case MPW_INTEGER:
				mpfr_mul_z (rp->data.fval, op1->data.fval,
					    op2->data.ival, GMP_RNDN);
				break;
			}
		} else  {
			switch(op1->type) {
			case MPW_RATIONAL:
				mpfr_mul_q (rp->data.fval, op2->data.fval,
					    op1->data.rval, GMP_RNDN);
				break;
			case MPW_INTEGER:
				mpfr_mul_z (rp->data.fval, op2->data.fval,
					    op1->data.ival, GMP_RNDN);
				break;
			}
		}
		break;
	case MPW_RATIONAL:
		{
			mpq_ptr op1_q, op2_q;
			mpq_t op1_tmp, op2_tmp;
			MPWL_MPQ (op1_q, op1, op1_tmp);
			MPWL_MPQ (op2_q, op2, op2_tmp);
			mpq_mul (rp->data.rval, op1_q, op2_q);
			mpwl_make_int (rp);
			MPWL_MPQ_KILL (op1_q, op1_tmp);
			MPWL_MPQ_KILL (op2_q, op2_tmp);
		}
		break;


	}

	if (rop != rp)
		mpwl_move (rop, &r);
}
