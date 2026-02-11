abs (const cl_N& x)
{


	if (realp(x)) {
		DeclareType(cl_R,x);
		return abs(x);
	} else {
		DeclareType(cl_C,x);
		return abs_inline(x);
	}
}

}
