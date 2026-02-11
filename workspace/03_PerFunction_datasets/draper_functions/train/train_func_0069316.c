L5()
{register object *base=vs_base;
	register object *sup=base+VM5; VC5
	vs_reserve(VM5);
	check_arg(2);vs_top=sup;
	{object V21=base[0]->c.c_cdr;
	base[2]= V21;}
	if(!(endp_prop(base[2]))){
	goto T36;}
	base[3]= Cnil;
	vs_top=(vs_base=base+3)+1;
	return;
	goto T36;
T36:;
	{object V22;
	V22= reverse(base[2]);
	{register object V23;
	register object V24;
	V23= cdr((V22));
	V24= car((V22));
	goto T42;
T42:;
	if(!(endp_prop((V23)))){
	goto T43;}
	base[3]= (V24);
	vs_top=(vs_base=base+3)+1;
	return;
	goto T43;
T43:;
	{object V25;
	V25= cdr((V23));
	{register object V26;
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V26= vs_base[0];
	V27= list(2,(V26),car((V23)));
	V28= make_cons(V27,Cnil);
	V24= list(3,((object)VV[12]),V28,list(4,((object)VV[11]),(V26),(V26),(V24)));}
	V23= (V25);}
	goto T42;}}
}
