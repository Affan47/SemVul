L60()
{register object *base=vs_base;
	register object *sup=base+VM60; VC60
	vs_check;
	{object V222;
	V222=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (V222);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
