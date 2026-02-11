Lunintern()
{
# line 896 "package.d"

	int narg;
	register object *DPPbase=vs_base;
#define	symbl	DPPbase[0]
#define	p	DPPbase[1+0]

	narg = vs_top - vs_base;
	if (narg < 1)
		too_few_arguments();
	if (narg <= 1 + 0) {
		vs_push(current_package());
		narg++;
	}
	if (narg > 1 + 1)
		too_many_arguments();

# line 897 "package.d"

	check_type_symbol(&symbl);
	check_package_designator(p);
	p = coerce_to_package(p);
	if (unintern(symbl, p))
		{
			vs_base[0] = Ct;
			vs_top = vs_base + 1;
			return;
		}
# line 902 "package.d"

	else
		{
			vs_base[0] = Cnil;
			vs_top = vs_base + 1;
			return;
		}
# line 904 "package.d"

#undef symbl
#undef p
}
