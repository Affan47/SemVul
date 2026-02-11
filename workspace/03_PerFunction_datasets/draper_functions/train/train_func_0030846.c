L178__WINDOW_SET_COLOR__dwtrans()
{register object *base=vs_base;
	register object *sup=base+VM178; VC178
	vs_check;
	{object V1126;
	object V1127;
	object V1128;
	V1126=(base[0]);
	V1127=(base[1]);
	vs_base=vs_base+2;
	if(vs_base>=vs_top){vs_top=sup;goto T4389;}
	V1128=(base[2]);
	vs_top=sup;
	goto T4390;
	goto T4389;
T4389:;
	V1128= Cnil;
	goto T4390;
T4390:;
	base[3]= (V1126);
	base[4]= CMPcar((V1127));
	base[5]= CMPcadr((V1127));
	base[6]= CMPcaddr((V1127));
	base[7]= (V1128);
	vs_top=(vs_base=base+3)+5;
	(void) (*Lnk309)();
	return;
	}
}
