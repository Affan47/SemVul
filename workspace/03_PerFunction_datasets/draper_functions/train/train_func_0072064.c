mpw_pow (mpw_ptr rop, mpw_ptr op1, mpw_ptr op2)
{
	if (MPW_IS_REAL (op1) && MPW_IS_REAL (op2)) {
		MAKE_REAL(rop);
		if (rop != op1 && rop != op2) {
			MAKE_EMPTY (rop->r, op1->r->type);
		} else {
			MAKE_COPY (rop->r);
		}
		if(mpwl_pow(rop->r,op1->r,op2->r)) {
			goto backup_mpw_pow;
		}
	} else if (MPW_IS_REAL (op2) &&
		   op2->r->type == MPW_INTEGER &&
		   op1->i->type != MPW_FLOAT &&
		   mpwl_zero_p (op1->r)) {
		MpwRealNum t = {{NULL}};
		MpwRealNum t2 = {{NULL}};
		mpwl_init_type (&t, op1->i->type);
		mpwl_init_type (&t2, op2->r->type);
		mpwl_set (&t2, op2->r);

		if (mpwl_pow (&t, op1->i, op2->r)) {
			mpwl_clear (&t2);
			mpwl_clear (&t);
			goto backup_mpw_pow;

		}

		if (mpwl_even_p (&t2)) {

			MAKE_REAL (rop);

			MAKE_COPY (rop->r);

			mpwl_div_ui (&t2, &t2, 2);
			if (mpwl_even_p (&t2)) {

				mpwl_set (rop->r, &t);
			} else {
				mpwl_neg (rop->r, &t);
			}
		} else {

			MAKE_IMAG (rop);

			MAKE_COPY (rop->i);

			mpwl_sub_ui (&t2, &t2, 1);
			mpwl_div_ui (&t2, &t2, 2);
			if (mpwl_even_p (&t2)) {

				mpwl_set (rop->i, &t);
			} else {
				mpwl_neg (rop->i, &t);
			}
		}

		mpwl_clear (&t2);
		mpwl_clear (&t);
	} else {
		goto backup_mpw_pow;
	}
	return;
backup_mpw_pow:
	if (mpwl_zero_p (op1->r) &&
	    mpwl_zero_p (op1->i)) {
		mpw_set_ui (rop, 0);
	} else {
		mpw_t tmp;
		mpw_init (tmp);
		mpw_ln (tmp, op1);
		mpw_mul (tmp, tmp, op2);
		mpw_exp (tmp, tmp);
		mpw_set (rop, tmp);
		mpw_clear (tmp);
	}
}
