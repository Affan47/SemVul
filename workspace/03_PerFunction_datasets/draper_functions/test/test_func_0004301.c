L21()
{register object *base=vs_base;
	register object *sup=base+VM21; VC21
	vs_check;
	bds_check;
	vs_top=sup;
	goto TTL;
TTL:;
	bds_bind(((object)VV[9]),((object)VV[73]));
	vs_base=vs_top;
	(void) (*Lnk103)();
	vs_top=sup;
	base[3]= vs_base[0];
	vs_top=(vs_base=base+3)+1;
	(void) (*Lnk104)();
	vs_top=sup;
	base[2]= vs_base[0];
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk105)();
	vs_top=sup;
	base[1]= vs_base[0];
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk106)();
	bds_unwind1;
	return;
}
