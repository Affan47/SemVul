L4()
{register object *base=vs_base;
	register object *sup=base+VM4; VC4
	vs_check;
	{object V16;
	object V17;
	object V18;
	V16=(base[0]);
	V17=(base[1]);
	V18=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((V17))!=Cnil){
	goto T31;}
	base[3]= Cnil;
	vs_top=(vs_base=base+3)+1;
	return;
	goto T31;
T31:;
	{object V20;
	V20= ((V18))->v.v_self[(long)11];
	base[3]= CMPcar((V20));
	base[4]= (V16);
	base[5]= CMPcdr((V20));
	vs_top=(vs_base=base+4)+2;
	super_funcall_no_event(base[3]);
	vs_top=sup;
	V19= vs_base[0];}
	base[3]= make_cons(V19,Cnil);
	vs_top=(vs_base=base+3)+1;
	return;
	}
}
