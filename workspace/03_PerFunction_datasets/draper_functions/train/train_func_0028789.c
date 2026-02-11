L30()
{register object *base=vs_base;
	register object *sup=base+VM30; VC30
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (((object)VV[59])->s.s_dbind);
	{object V87;
	object V88= base[1];
	if(V88==Cnil){
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	base[0]=V87=MMcons(Cnil,Cnil);
	goto T230;
T230:;
	(V87->c.c_car)= make_cons(CMPcar((V88->c.c_car)),((CMPcdr((V88->c.c_car)))==Cnil?Ct:Cnil));
	if((V88=MMcdr(V88))==Cnil){
	vs_top=(vs_base=base+0)+1;
	return;}
	V87=MMcdr(V87)=MMcons(Cnil,Cnil);
	goto T230;}
}
