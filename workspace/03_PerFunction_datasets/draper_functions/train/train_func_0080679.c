operator/ (const cl_RA& x, const cl_F& y)
{
	if (eq(x,0)) { return 0; }
	floatcase(y
	, 	if (integerp(x)) {
				DeclareType(cl_I,x);
				return cl_I_to_SF(x) / y;
			} else
				return cl_RA_to_SF(x) / y;
	, 	if (integerp(x)) {
				DeclareType(cl_I,x);
				return cl_I_to_FF(x) / y;
			} else
				return cl_RA_to_FF(x) / y;
	, 	if (integerp(x)) {
				DeclareType(cl_I,x);
				return cl_I_to_DF(x) / y;
			} else
				return cl_RA_to_DF(x) / y;
	, 	if (integerp(x)) {
				DeclareType(cl_I,x);
				return cl_I_LF_div(x,y);
			} else
				return cl_RA_LF_div(x,y);
	);
}
