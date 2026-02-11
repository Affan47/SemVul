expt (const cl_R& x, const cl_I& y)
{
	if (eq(y,0)) { return 1; }
	var bool y_negative = minusp(y);
	var cl_I abs_y = (y_negative ? -y : y);
	var cl_R z = expt_pos(x,abs_y);
	return (y_negative ? recip(z) : z);
}
