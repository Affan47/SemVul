L44()
{register object *base=vs_base;
	register object *sup=base+VM44; VC44
	vs_reserve(VM44);
	ihs_check;
	check_arg(1);
	base[0]=MMcons(base[0],Cnil);
	vs_top=sup;
	base[1]=
	make_cclosure_new(LC145,Cnil,base[0],Cdata);
	vs_top=(vs_base=base+1)+1;
	return;
}
