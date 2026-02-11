L48()
{register object *base=vs_base;
	register object *sup=base+VM48; VC48
	vs_check;
	{object V84;
	V84=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V85;
	register object V86;
	V85= reverse((V84));
	V86= ((object)VV[66]);
	goto T93;
T93:;
	if(((V85))!=Cnil){
	goto T94;}
	base[1]= (V86);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T94;
T94:;
	{object V87;
	V87= CMPcdr((V85));
	base[1]= CMPcar((V85));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk54)();
	vs_top=sup;
	V88= vs_base[0];
	V86= (VFUN_NARGS=3,(*(LnkLI86))(((object)VV[6]),V88,(V86)));
	V85= (V87);}
	goto T93;}
	}
}
