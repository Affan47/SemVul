L3()
{register object *base=vs_base;
	register object *sup=base+VM3; VC3
	vs_check;vs_top=sup;
	{object V32=base[0]->c.c_cdr;
	base[2]= (V32->c.c_car);
	V32=V32->c.c_cdr;
	base[3]= (V32->c.c_car);}
	if(!(type_of(base[3])!=t_cons)){
	goto T48;}
	base[4]= (*(LnkLI246))(base[2],base[3]);
	vs_top=(vs_base=base+4)+1;
	return;
	goto T48;
T48:;
	{object V33;
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V33= vs_base[0];
	V34= list(2,(V33),base[3]);
	V35= make_cons(V34,Cnil);
	base[4]= list(3,((object)VV[12]),V35,(*(LnkLI246))(base[2],(V33)));
	vs_top=(vs_base=base+4)+1;
	return;}
}
