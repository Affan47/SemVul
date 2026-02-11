L14()
{register object *base=vs_base;
	register object *sup=base+VM14; VC14
	vs_check;
	{object V73;
	object V74;
	V73=(base[0]);
	V74=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (immnum_minusp((V73))?Ct:Cnil);
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
