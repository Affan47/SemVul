__ldexp(double value, int exp)
{
	if(!__finite(value)||value==0.0) return value;
	value = __scalbn(value,exp);
	if(!__finite(value)||value==0.0) __set_errno (ERANGE);
	return value;
}
