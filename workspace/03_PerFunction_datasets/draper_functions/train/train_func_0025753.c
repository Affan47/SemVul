L1()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	{object V1;
	object V2;
	object V3;
	V1=(base[0]);
	V2=(base[1]);
	V3=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V4;
	V4= ((V3))->v.v_self[(long)21];
	base[3]= CMPcar((V4));
	base[4]= (V2);
	base[5]= CMPcdr((V4));
	vs_top=(vs_base=base+4)+2;
	super_funcall_no_event(base[3]);
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T2;}}
	base[3]= (*(LnkLI50))(((object)VV[0]));
	vs_top=(vs_base=base+3)+1;
	return;
	goto T2;
T2:;
	{object V5;
	V5= ((V3))->v.v_self[(long)25];
	base[3]= CMPcar((V5));
	base[4]= (V1);
	base[5]= (V2);
	base[6]= CMPcdr((V5));
	vs_top=(vs_base=base+4)+3;
	super_funcall_no_event(base[3]);
	return;}
	}
}
