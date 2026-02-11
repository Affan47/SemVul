truncate2 (const cl_F& x)
{
	floatcase(x
	,	var cl_SF q = ftruncate(x); return cl_F_div_t(cl_SF_to_I(q),x-q);
	,	var cl_FF q = ftruncate(x); return cl_F_div_t(cl_FF_to_I(q),x-q);
	,	var cl_DF q = ftruncate(x); return cl_F_div_t(cl_DF_to_I(q),x-q);
	,	var cl_LF q = ftruncate(x); return cl_F_div_t(cl_LF_to_I(q),LF_LF_minus_LF(x,q));
	);
}
