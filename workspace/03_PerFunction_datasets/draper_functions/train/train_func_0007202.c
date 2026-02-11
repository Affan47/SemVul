L15()
{register object *base=vs_base;
	register object *sup=base+VM15; VC15
	vs_check;
	{object V33;
	object V34;
	V33=(base[0]);
	V34=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;{object V35;
	base[2]= (V33);
	base[3]= (V34);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk139)();
	vs_top=sup;
	V35= vs_base[0];
	if(V35==Cnil)goto T88;
	base[2]= V35;
	vs_top=(vs_base=base+2)+1;
	return;
	goto T88;
T88:;}
	base[2]= (V33);
	base[3]= (V34);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk141)();
	return;
	}
}
