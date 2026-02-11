cl_R_to_SF (const cl_R& x)
{
	realcase6(x
	,	return cl_I_to_SF(x);
	,	return cl_RA_to_SF(x);
	,	return x;
	,	return cl_FF_to_SF(x);
	,	return cl_DF_to_SF(x);
	,	return cl_LF_to_SF(x);
	);
}
