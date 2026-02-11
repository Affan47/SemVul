L13()
{register object *base=vs_base;
	register object *sup=base+VM13; VC13
	vs_check;
	{object V76;
	object V77;
	V76=(base[0]);
	V77=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= ((object)VV[14]);
	vs_top=(vs_base=base+2)+1;
	Lfloat_digits();
	vs_top=sup;
	V78= vs_base[0];
	{object V80;
	V80= ((V77))->v.v_self[(long)26];
	base[2]= CMPcar((V80));
	base[3]= (V76);
	base[4]= CMPcdr((V80));
	vs_top=(vs_base=base+3)+2;
	super_funcall_no_event(base[2]);
	vs_top=sup;
	V79= vs_base[0];}
	V81= immnum_plus(V78,V79);
	base[2]= immnum_minus(V81,small_fixnum(1));
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
