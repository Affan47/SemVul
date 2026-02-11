L40()
{register object *base=vs_base;
	register object *sup=base+VM40; VC40
	vs_check;
	{object V154;
	V154=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (V154);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk182)();
	vs_top=sup;
	V155= vs_base[0];
	base[1]= ((((V155)==Cnil?Ct:Cnil))==Cnil?Ct:Cnil);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
