mpw_even_p(mpw_ptr op)
{
	if G_LIKELY (MPW_IS_REAL (op)) {
		return mpwl_even_p(op->r);
	} else {
		gel_error_num=GEL_NUMERICAL_MPW_ERROR;
		gel_errorout (_("%s: can't work on complex numbers"),
			      "even_p");
		return FALSE;
	}
}
