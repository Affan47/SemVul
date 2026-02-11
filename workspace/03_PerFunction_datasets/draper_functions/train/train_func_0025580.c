LI9(object first,...)
{
	va_list ap;
	int narg = VFUN_NARGS; VMB9 VMS9 VMV9
	{object V77;
	object V78;
	object V79;
	va_start(ap,first);
	narg= narg - 0;
	{
	parse_key_new_new(narg,Vcs +0,(struct key *)(void *)&LI9key,first,ap);
	V77=(Vcs[0]);
	V78=(Vcs[1]);
	V79=(Vcs[2]);
	base[0]= ((object)VV[25]);
	base[1]= (V77);
	base[2]= (V78);
	base[3]= (V79);
	vs_top=(vs_base=base+0)+4;
	siLmake_structure();
	vs_top=sup;
	{object V80 = vs_base[0];
	VMR9(V80)}
	va_end(ap);
	base[0]=base[0];
	return Cnil;}
	}}
