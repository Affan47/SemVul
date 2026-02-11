round2 (const cl_RA& x)
{


	if (integerp(x)) {
		DeclareType(cl_I,x);

		return cl_RA_div_t(x,0);
	} else {
		DeclareType(cl_RT,x);
		var const cl_I& a = numerator(x);
		var const cl_I& b = denominator(x);
		var cl_I_div_t q_r = round2(a,b);
		var cl_I& q = q_r.quotient;
		var cl_I& r = q_r.remainder;
		return cl_RA_div_t(q,I_I_to_RT(r,b));
	}
}
