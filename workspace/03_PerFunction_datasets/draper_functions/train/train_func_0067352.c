LI41__AUTOLOAD__top(V336,V337)

object V336;object V337;
{	 VMB40 VMS40 VMV40
	bds_check;
	goto TTL;
TTL:;
	base[0]=MMcons((V337),Cnil);
	base[1]=MMcons((V336),base[0]);
	bds_bind(((object)VV[167]),Ct);
	base[3]= (base[1]->c.c_car);
	vs_top=(vs_base=base+3)+1;
	Lfboundp();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T1392;}
	{object V338 = Ct;
	bds_unwind1;
	VMR40(V338)}
	goto T1392;
T1392:;
	base[3]= (base[1]->c.c_car);
	base[4]=
	make_cclosure_new(LC51__CLOSURE__top,Cnil,base[1],Cdata);
	vs_top=(vs_base=base+3)+2;
	siLfset();
	vs_top=sup;
	{object V339 = vs_base[0];
	bds_unwind1;
	VMR40(V339)}
	base[0]=base[0];
	return Cnil;
}
