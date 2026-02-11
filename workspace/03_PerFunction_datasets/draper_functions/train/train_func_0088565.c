cl_R_to_LF (const cl_R& x, uintC len)
{
	realcase6(x
	,	return cl_I_to_LF(x,len);
	,	return cl_RA_to_LF(x,len);
	,	return cl_SF_to_LF(x,len);
	,	return cl_FF_to_LF(x,len);
	,	return cl_DF_to_LF(x,len);
	,	return LF_to_LF(x,len);
	);
}
