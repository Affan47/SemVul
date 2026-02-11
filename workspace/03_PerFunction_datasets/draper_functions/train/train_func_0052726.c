L63()
{register object *base=vs_base;
	register object *sup=base+VM63; VC63
	vs_check;
	{register object V668;
	object V669;
	object V670;
	V668=(base[0]);
	V669=(base[1]);
	vs_base=vs_base+2;
	if(vs_base>=vs_top){vs_top=sup;goto T1583;}
	V670=(base[2]);
	vs_top=sup;
	goto T1584;
	goto T1583;
T1583:;
	V670= (((object)VV[233])->s.s_dbind);
	goto T1584;
T1584:;
	{register object V671;
	V671= Cnil;
	{register object V672;
	V672= (V669);
	goto T1588;
T1588:;
	if(((V672))!=Cnil){
	goto T1589;}
	base[3]= (V671);
	base[4]= Cnil;
	vs_top=(vs_base=base+3)+2;
	return;
	goto T1589;
T1589:;
	if(!(eql(CMPcar((V672)),(V668)))){
	goto T1597;}
	base[3]= (V672);
	base[4]= Ct;
	vs_top=(vs_base=base+3)+2;
	return;
	goto T1597;
T1597:;
	base[3]= (V668);
	base[4]= CMPcar((V672));
	vs_top=(vs_base=base+3)+2;
	super_funcall_no_event((V670));
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T1595;}
	base[3]= (V671);
	base[4]= Cnil;
	vs_top=(vs_base=base+3)+2;
	return;
	goto T1595;
T1595:;
	V671= (V672);
	V672= CMPcdr((V672));
	goto T1588;}}
	}
}
