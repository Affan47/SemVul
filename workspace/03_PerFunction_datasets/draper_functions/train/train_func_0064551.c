cos_sin (const cl_R& x)
{


	if (rationalp(x)) {
		DeclareType(cl_RA,x);
		if (zerop(x))
			return cos_sin_t(1,0);
		return cos_sin(cl_float(x));
	} else {
		DeclareType(cl_F,x);
		return cos_sin(x);
	}
}
