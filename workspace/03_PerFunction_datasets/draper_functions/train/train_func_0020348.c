L64()
{register object *base=vs_base;
	register object *sup=base+VM64; VC64
	vs_check;
	{object V196;
	V196=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (V196);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk70)();
	vs_top=sup;
	V197= vs_base[0];
	base[1]= CMPcddr(V197);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
