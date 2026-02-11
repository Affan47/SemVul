_asin (const cl_N& z)
{
	if (realp(z)) {
		DeclareType(cl_R,z);
		return asinh(0,z);
	} else {
		DeclareType(cl_C,z);
		return asinh(-imagpart(z),realpart(z));
	}
}
