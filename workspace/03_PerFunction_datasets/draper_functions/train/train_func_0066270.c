log (const cl_R& a, const cl_R& b)
{


 {	Mutable(cl_R,a);
	Mutable(cl_R,b);
	if (rationalp(b)) {

		if (eq(b,1)) { throw division_by_0_exception(); }
		if (rationalp(a)) {

			var cl_RA l;
			if (logp(The(cl_RA)(a),The(cl_RA)(b),&l))
				return l;

			a = cl_float(The(cl_RA)(a)); b = cl_float(The(cl_RA)(b));
		} else

			b = cl_float(The(cl_RA)(b),The(cl_F)(a));
	} else {

		if (rationalp(a)) {
			if (eq(a,1)) { return 0; }
			a = cl_float(The(cl_RA)(a),The(cl_F)(b));
		}
	}

	return ln(The(cl_F)(a)) / ln(The(cl_F)(b));
}}
