L41()
{register object *base=vs_base;
	register object *sup=base+VM41; VC41
	vs_check;
	{object V608;
	object V609;
	V608=(base[0]);
	V609=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V610;
	V610= ((V609))->v.v_self[(long)201];
	base[2]= CMPcar((V610));
	base[3]= elt((V609),(long)196);
	base[4]= elt((V609),(long)197);
	base[5]= (V608);
	base[6]= CMPcdr((V610));
	vs_top=(vs_base=base+3)+4;
	super_funcall_no_event(base[2]);
	return;}
	}
}
