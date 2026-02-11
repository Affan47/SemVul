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
	V4= ((V3))->v.v_self[(long)9];
	base[3]= CMPcar((V4));
	{object V5;
	V5= ((V3))->v.v_self[(long)8];
	base[5]= CMPcar((V5));
	base[6]= (V1);
	base[7]= (V2);
	base[8]= CMPcdr((V5));
	vs_top=(vs_base=base+6)+3;
	super_funcall_no_event(base[5]);
	vs_top=sup;
	base[4]= vs_base[0];}
	{object V6;
	V6= ((V3))->v.v_self[(long)8];
	base[6]= CMPcar((V6));
	base[7]= (V2);
	base[8]= (V1);
	base[9]= CMPcdr((V6));
	vs_top=(vs_base=base+7)+3;
	super_funcall_no_event(base[6]);
	vs_top=sup;
	base[5]= vs_base[0];}
	base[6]= CMPcdr((V4));
	vs_top=(vs_base=base+4)+3;
	super_funcall_no_event(base[3]);
	return;}
	}
}
