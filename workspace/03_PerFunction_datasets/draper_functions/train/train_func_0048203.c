L9__WHILE__evalmacros()
{register object *base=vs_base;
	register object *sup=base+VM9; VC9
	vs_reserve(VM9);
	check_arg(2);vs_top=sup;
	{object V58=base[0]->c.c_cdr;
	if(endp(V58))invalid_macro_call();
	base[2]= (V58->c.c_car);
	V58=V58->c.c_cdr;
	base[3]= V58;}
	base[4]= listA(3,((object)VV[19]),list(3,((object)VV[20]),base[2],((object)VV[21])),base[3]);
	vs_top=(vs_base=base+4)+1;
	return;
}
