cl_float (const cl_RA& x)
{
	floatformatcase(default_float_format
	,	return cl_RA_to_SF(x);
	,	return cl_RA_to_FF(x);
	,	return cl_RA_to_DF(x);
	,	return cl_RA_to_LF(x,len);
	);
}

}
