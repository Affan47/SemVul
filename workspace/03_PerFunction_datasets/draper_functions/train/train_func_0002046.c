L2()
{register object *base=vs_base;
	register object *sup=base+VM2; VC2
	vs_check;
	{object V4;
	V4=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (V4);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk7)();
	vs_top=sup;
	base[1]= vs_base[0];
	base[2]= ((object)VV[0]);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk8)();
	return;
	}
}
