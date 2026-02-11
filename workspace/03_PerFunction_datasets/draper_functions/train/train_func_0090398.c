L18()
{register object *base=vs_base;
	register object *sup=base+VM18; VC18
	vs_check;
	{object V42;
	object V43;
	V42=(base[0]);
	V43=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((((object)VV[7])->s.s_dbind))!=Cnil){
	goto T137;}
	{object V44;
	{register object x= (V42),V45= (((object)VV[33])->s.s_dbind);
	while(V45!=Cnil)
	if(eql(x,V45->c.c_car->c.c_car) &&V45->c.c_car != Cnil){
	V44= (V45->c.c_car);
	goto T139;
	}else V45=V45->c.c_cdr;
	V44= Cnil;}
	goto T139;
T139:;
	V46= make_cons((V43),CMPcdr((V44)));
	((V44))->c.c_cdr = SAFE_CDR(V46);
	base[2]= (V44);
	vs_top=(vs_base=base+2)+1;
	return;}
	goto T137;
T137:;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
