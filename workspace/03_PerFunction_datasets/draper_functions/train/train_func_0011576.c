LI2()

{	 VMB2 VMS2 VMV2
	goto TTL;
TTL:;
	{register object x= ((object)VV[0]),V3= (((object)VV[1])->s.s_dbind);
	while(V3!=Cnil)
	if(eql(x,V3->c.c_car)){
	goto T8;
	}else V3=V3->c.c_cdr;
	goto T5;}
	goto T8;
T8:;
	{register object x= ((object)VV[2]),V4= (((object)VV[1])->s.s_dbind);
	while(V4!=Cnil)
	if(eql(x,V4->c.c_car)){
	goto T9;
	}else V4=V4->c.c_cdr;
	goto T5;}
	goto T9;
T9:;
	{register object V5;
	register object V6;
	V5= ((object)VV[3]);
	V6= CMPcar((V5));
	goto T14;
T14:;
	if(!(((V5))==Cnil)){
	goto T15;}
	goto T10;
	goto T15;
T15:;
	base[0]= (V6);
	vs_top=(vs_base=base+0)+1;
	Lfboundp();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T19;}
	base[0]= (V6);
	vs_top=(vs_base=base+0)+1;
	Lfmakunbound();
	vs_top=sup;
	goto T19;
T19:;
	V5= CMPcdr((V5));
	V6= CMPcar((V5));
	goto T14;}
	goto T10;
T10:;
	(((object)VV[1])->s.s_dbind)= (VFUN_NARGS=2,(*(LnkLI260))(((object)VV[2]),(((object)VV[1])->s.s_dbind),small_fixnum(0)));
	goto T5;
T5:;
	{object V7 = Cnil;
	VMR2(V7)}
	base[0]=base[0];
	return Cnil;
}
