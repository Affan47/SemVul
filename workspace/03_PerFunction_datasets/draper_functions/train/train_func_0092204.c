Lchar_neq()
{
# line 172 "character.d"

	int i, j;
	int narg;
	register object *DPPbase=vs_base;
#define	c	DPPbase[0]

	narg = vs_top - vs_base;
	if (narg < 1)
		too_few_arguments();

# line 174 "character.d"

	check_type_character(&c);
	for (i = 0;  i < narg;  i++)
		check_type_character(&vs_base[i]);
	if (narg == 0)
		{
			vs_base[0] = Ct;
			vs_top = vs_base + 1;
			return;
		}
# line 179 "character.d"

	for (i = 1;  i < narg;  i++)
		for (j = 0;  j < i;  j++)
			if (char_eq(vs_base[j], vs_base[i]))
				{
					vs_base[0] = Cnil;
					vs_top = vs_base + 1;
					return;
				}
# line 183 "character.d"

	{
		vs_base[0] = Ct;
		vs_top = vs_base + 1;
		return;
	}
# line 184 "character.d"

#undef c
}
