mpwl_getstring(MpwRealNum * num, int max_digits,
	       gboolean scientific_notation,
	       gboolean results_as_floats,
	       gboolean mixed_fractions,
	       GelOutputStyle style,
	       int integer_output_base,
	       const char *postfix,
	       int chop)
{
	mpfr_t fr;
	char *p;
	switch(num->type) {
	case MPW_RATIONAL:
		if(results_as_floats) {
			mpfr_init (fr);
			mpfr_set_q (fr, num->data.rval, GMP_RNDN);
			p=str_getstring_f(fr,max_digits,
					  scientific_notation, postfix,
					  chop);
			mpfr_clear(fr);
			return p;
		}
		return str_getstring_q(num->data.rval,
				       max_digits,
				       scientific_notation,
				       mixed_fractions,
				       style,
				       postfix,
				       chop);
	case MPW_INTEGER:
		if(results_as_floats) {
			mpfr_init_set_z (fr, num->data.ival, GMP_RNDN);
			p=str_getstring_f(fr,max_digits,
					  scientific_notation,
					  postfix,
					  -1 );
			mpfr_clear(fr);
			return p;
		}
		return str_getstring_z(num->data.ival,max_digits,
				       scientific_notation,
				       integer_output_base,
				       postfix);
	case MPW_FLOAT:
		return str_getstring_f(num->data.fval,max_digits,
				       scientific_notation,
				       postfix,
				       chop);
	}

	return NULL;
}
