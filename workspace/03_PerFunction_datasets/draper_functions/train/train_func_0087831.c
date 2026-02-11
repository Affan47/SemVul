LI10__CLEANUP__debug()

{	 VMB10 VMS10 VMV10
	goto TTL;
TTL:;
	{register object V81;
	register object V82;
	V81= symbol_value(((object)VV[26]));
	V82= car((V81));
	goto T280;
T280:;
	if(!(endp_prop((V81)))){
	goto T281;}
	{object V83 = Cnil;
	VMR10(V83)}
	goto T281;
T281:;
	base[0]= structure_ref((V82),((object)VV[25]),(long)0);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk128)();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T285;}
	setq(((object)VV[26]),(VFUN_NARGS=2,(*(LnkLI129))((V82),symbol_value(((object)VV[26])),small_fixnum(0))));
	goto T285;
T285:;
	V81= cdr((V81));
	V82= car((V81));
	goto T280;}
	base[0]=base[0];
	return Cnil;
}
