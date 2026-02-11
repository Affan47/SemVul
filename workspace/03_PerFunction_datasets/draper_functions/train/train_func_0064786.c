L21()
{register object *base=vs_base;
	register object *sup=base+VM21; VC21
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;{object V74;
	V74= (((object)VV[9])->s.s_dbind);
	vs_base=vs_top;
	(void) (*Lnk147)();
	vs_top=sup;
	if(!(((((object)VV[34])->s.s_dbind))==(((object)VV[79])))){
	goto T253;}
	base[0]= ((object)VV[27]);
	base[2]= (((object)VV[80])->s.s_dbind);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk163)();
	vs_top=sup;
	base[1]= vs_base[0];
	base[2]= ((object)VV[81]);
	vs_top=(vs_base=base+0)+3;
	(void) (*Lnk148)();
	vs_top=sup;
	V75= vs_base[0];
	goto T250;
	goto T253;
T253:;
	if(!(immnum_eq((((object)VV[82])->s.s_dbind),small_fixnum(1)))){
	goto T260;}
	vs_base=vs_top;
	(void) (*Lnk164)();
	vs_top=sup;
	V75= vs_base[0];
	goto T250;
	goto T260;
T260:;
	base[0]= ((object)VV[83]);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk145)();
	vs_top=sup;
	V75= vs_base[0];
	goto T250;
T250:;
	base[0]= list(2,V74,V75);
	vs_top=(vs_base=base+0)+1;
	return;}
}
