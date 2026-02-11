Lnbutlast()
{
# line 1060 "list.d"

	int i;
	object x;
	int narg;
	register object *DPPbase=vs_base;
#define	lis	DPPbase[0]
#define	nn	DPPbase[1+0]

	narg = vs_top - vs_base;
	if (narg < 1)
		too_few_arguments();
	if (narg <= 1 + 0) {
		vs_push(make_fixnum(1));
		narg++;
	}
	if (narg > 1 + 1)
		too_many_arguments();

# line 1063 "list.d"

	check_type_non_negative_integer(&nn);
	if (!listp(lis))
	  FEwrong_type_argument(sLlist, lis);
	if (type_of(nn) != t_fixnum)
		{
			vs_base[0] = Cnil;
			vs_top = vs_base + 1;
			return;
		}
# line 1068 "list.d"

	for (i = 0, x = lis;  consp(x);  i++, x = x->c.c_cdr);
	if (i <= fix((nn)))
		{
			vs_base[0] = Cnil;
			vs_top = vs_base + 1;
			return;
		}
# line 1071 "list.d"

	for (i -= fix((nn)), x = lis;  --i > 0;  x = x->c.c_cdr)
		;
	x->c.c_cdr = Cnil;
	{
		vs_base[0] = lis;
		vs_top = vs_base + 1;
		return;
	}
# line 1075 "list.d"

#undef lis
#undef nn
}
