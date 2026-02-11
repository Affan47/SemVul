L6()
{register object *base=vs_base;
	register object *sup=base+VM6; VC6
	vs_check;
	{object V29;
	object V30;
	V29=(base[0]);
	V30=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V31;
	V31= ((V30))->v.v_self[(long)37];
	base[2]= CMPcar((V31));
	base[3]= (V29);
	{object V33;
	V33= ((V30))->v.v_self[(long)35];
	base[5]= CMPcar((V33));
	base[6]= CMPcdr((V33));
	vs_top=(vs_base=base+6)+1;
	super_funcall_no_event(base[5]);
	vs_top=sup;
	V32= vs_base[0];}
	{object V35;
	V35= ((V30))->v.v_self[(long)36];
	base[5]= CMPcar((V35));
	base[6]= CMPcdr((V35));
	vs_top=(vs_base=base+6)+1;
	super_funcall_no_event(base[5]);
	vs_top=sup;
	V34= vs_base[0];}
	base[4]= (*(LnkLI16))(V32,V34);
	base[5]= CMPcdr((V31));
	vs_top=(vs_base=base+3)+3;
	super_funcall_no_event(base[2]);
	return;}
	}
}
