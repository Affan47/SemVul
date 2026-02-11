LI3(V21)

register object V21;
{	 VMB3 VMS3 VMV3
	goto TTL;
TTL:;
	if(!(type_of((V21))!=t_cons)){
	goto T31;}
	base[0]= (V21);
	base[1]= ((object)VV[2]);
	vs_top=(vs_base=base+0)+2;
	(void) (*Lnk45)();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T34;}
	V22 = CMPmake_fixnum((long)((fix(STREF(object,(V21),48)))+(fix((((object)VV[3])->s.s_dbind)))));
	V23= Ct;
	STSET(object,(V21),48, V22);
	{object V24 = V22;
	VMR3(V24)}
	goto T34;
T34:;
	{object V25 = Cnil;
	VMR3(V25)}
	goto T31;
T31:;
	(void)((*(LnkLI47))(CMPcar((V21))));
	V21= CMPcdr((V21));
	goto TTL;
	base[0]=base[0];
	return Cnil;
}
