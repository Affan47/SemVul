L7()
{register object *base=vs_base;
	register object *sup=base+VM7; VC7
	vs_check;
	{object V36;
	V36=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!((CMPcar((V36)))==(((object)VV[16])))){
	goto T100;}
	base[1]= make_cons((V36),Cnil);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T100;
T100:;
	base[1]= ((object)VV[17]);
	{object V38;
	object V39= CMPcdr((V36));
	if(V39==Cnil){
	V37= Cnil;
	goto T104;}
	base[3]=V38=MMcons(Cnil,Cnil);
	goto T105;
T105:;
	base[4]= (V39->c.c_car);
	vs_top=(vs_base=base+4)+1;
	(void) (*Lnk136)();
	vs_top=sup;
	(V38->c.c_car)= vs_base[0];
	if((V39=MMcdr(V39))==Cnil){
	V37= base[3];
	goto T104;}
	V38=MMcdr(V38)=MMcons(Cnil,Cnil);
	goto T105;}
	goto T104;
T104:;
	base[2]= make_cons(Cnil,V37);
	base[3]= Cnil;
	vs_top=(vs_base=base+1)+3;
	(void) (*Lnk137)();
	return;
	}
}
