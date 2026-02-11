L13()
{register object *base=vs_base;
	register object *sup=base+VM13; VC13
	vs_check;
	bds_check;
	{object V61;
	V61=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	bds_bind(((object)VV[18]),Cnil);
	base[2]= (V61);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk49)();
	bds_unwind1;
	return;
	}
}
