fixnnint(object x)
{
	if (type_of(x) != t_fixnum || fix(x) < 0)
		FEerror("~S is not a non-negative fixnum.", 1, x);
	return(fix(x));
}
