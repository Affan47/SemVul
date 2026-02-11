L20()
{register object *base=vs_base;
	register object *sup=base+VM20; VC20
	vs_check;
	{object V99;
	object V100;
	object V101;
	object V102;
	V99=(base[0]);
	V100=(base[1]);
	V101=(base[2]);
	V102=(base[3]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V103;
	V103= ((V102))->v.v_self[(long)67];
	base[4]= CMPcar((V103));
	base[5]= (V99);
	{object V105;
	V105= ((V102))->v.v_self[(long)69];
	base[7]= CMPcar((V105));
	base[8]= (V100);
	base[9]= CMPcdr((V105));
	vs_top=(vs_base=base+8)+2;
	super_funcall_no_event(base[7]);
	vs_top=sup;
	V104= vs_base[0];}
	base[6]= make_cons(V104,Cnil);
	base[7]= make_cons((V101),Cnil);
	base[8]= CMPcdr((V103));
	vs_top=(vs_base=base+5)+4;
	super_funcall_no_event(base[4]);
	return;}
	}
}
