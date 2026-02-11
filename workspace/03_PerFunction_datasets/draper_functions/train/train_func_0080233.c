cl_ln10 (const cl_F& y)
{
	floattypecase(y
	,	return cl_SF_ln10();
	,	return cl_FF_ln10();
	,	return cl_DF_ln10();
	,	return cl_ln10(TheLfloat(y)->len);
	);
}
