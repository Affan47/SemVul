cdr(x)
object x;
{
	if (x == Cnil)
		return(x);
	if (type_of(x) == t_cons)
		return(x->c.c_cdr);
	FEwrong_type_argument(sLlist, x);
	return(Cnil);
}
