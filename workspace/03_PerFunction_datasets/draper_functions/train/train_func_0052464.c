L10()
{register object *base=vs_base;
	register object *sup=base+VM10; VC10
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	{object V36 =(((object)VV[19]))->s.s_plist;
	 object ind= ((object)VV[7]);
	while(V36!=Cnil){
	if(V36->c.c_car==ind){
	V35= (V36->c.c_cdr->c.c_car);
	goto T169;
	}else V36=V36->c.c_cdr->c.c_cdr;}
	V35= Cnil;}
	goto T169;
T169:;
	(void)(sputprop(((object)VV[19]),((object)VV[23]),V35));
	{object V38 =(((object)VV[18]))->s.s_plist;
	 object ind= ((object)VV[7]);
	while(V38!=Cnil){
	if(V38->c.c_car==ind){
	V37= (V38->c.c_cdr->c.c_car);
	goto T171;
	}else V38=V38->c.c_cdr->c.c_cdr;}
	V37= Cnil;}
	goto T171;
T171:;
	(void)(sputprop(((object)VV[18]),((object)VV[23]),V37));
	(void)(sputprop(((object)VV[19]),((object)VV[7]),small_fixnum(0)));
	base[0]= sputprop(((object)VV[18]),((object)VV[7]),small_fixnum(0));
	vs_top=(vs_base=base+0)+1;
	return;
}
