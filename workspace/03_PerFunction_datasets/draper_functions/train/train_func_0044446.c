L56()
{register object *base=vs_base;
	register object *sup=base+VM56; VC56
	vs_check;
	{object V176;
	object V177;
	V176=(base[0]);
	V177=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[4]= ((object)VV[56]);
	vs_top=(vs_base=base+4)+1;
	(void) (*Lnk105)();
	vs_top=sup;
	base[3]= vs_base[0];
	base[4]= (V176);
	vs_top=(vs_base=base+3)+2;
	(void) (*Lnk106)();
	vs_top=sup;
	base[2]= vs_base[0];
	base[3]= (V177);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk106)();
	return;
	}
}
