contagion (const cl_N& x)
{
	if (realp(x)) {
		DeclareType(cl_R,x);
		return x;
	} else {
		DeclareType(cl_C,x);
		return contagion(realpart(x),imagpart(x));
	}
}
