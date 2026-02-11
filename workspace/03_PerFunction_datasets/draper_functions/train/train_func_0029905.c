mpwl_pow (MpwRealNum *rop, MpwRealNum *op1, MpwRealNum *op2)
{
	int sgn1 = mpwl_sgn(op1);
	int sgn2 = mpwl_sgn(op2);
	if (sgn2 == 0) {
		mpwl_set_ui(rop,1);
		return FALSE;
	} else if (sgn1 == 0) {
		mpwl_set_ui(rop,0);
		return FALSE;
	}

	switch(op2->type) {
	case MPW_FLOAT: return mpwl_pow_f(rop,op1,op2);
	case MPW_RATIONAL: return mpwl_pow_q(rop,op1,op2);
	case MPW_INTEGER: mpwl_pow_z(rop,op1,op2); break;
	}
	return FALSE;
}
