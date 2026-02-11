LC3__OPTION_TEST__defpackage(base0)
register object *base0;
{	register object *base=vs_base;
	register object *sup=base+VM3; VC3
	vs_check;
	{object V174;
	object V175;
	V174=(base[0]);
	V175=(base[1]);
	vs_top=sup;
	if(!(type_of((V175))==t_cons)){
	goto T445;}
	base[2]= (equal(CMPcar((V175)),(V174))?Ct:Cnil);
	vs_top=(vs_base=base+2)+1;
	return;
	goto T445;
T445:;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
