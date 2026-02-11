L16()
{register object *base=vs_base;
	register object *sup=base+VM16; VC16
	vs_check;
	{object V246;
	object V247;
	object V248;
	V246=(base[0]);
	V247=(base[1]);
	V248=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V249;
	V249= ((V248))->v.v_self[(long)71];
	base[3]= CMPcar((V249));
	base[4]= (V246);
	base[5]= (V247);
	base[6]= elt((V248),(long)75);
	base[7]= elt((V248),(long)76);
	base[8]= CMPcdr((V249));
	vs_top=(vs_base=base+4)+5;
	super_funcall_no_event(base[3]);
	return;}
	}
}
