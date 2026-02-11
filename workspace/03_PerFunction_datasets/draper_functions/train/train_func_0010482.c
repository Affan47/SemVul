L57()
{register object *base=vs_base;
	register object *sup=base+VM57; VC57
	vs_check;
	{object V178;
	object V179;
	object V180;
	V178=(base[0]);
	V179=(base[1]);
	V180=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[6]= ((object)VV[57]);
	vs_top=(vs_base=base+6)+1;
	(void) (*Lnk105)();
	vs_top=sup;
	base[5]= vs_base[0];
	base[6]= (V178);
	vs_top=(vs_base=base+5)+2;
	(void) (*Lnk106)();
	vs_top=sup;
	base[4]= vs_base[0];
	base[5]= (V179);
	vs_top=(vs_base=base+4)+2;
	(void) (*Lnk106)();
	vs_top=sup;
	base[3]= vs_base[0];
	base[4]= (V180);
	vs_top=(vs_base=base+3)+2;
	(void) (*Lnk106)();
	return;
	}
}
