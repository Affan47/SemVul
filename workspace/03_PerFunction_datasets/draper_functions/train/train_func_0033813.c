L20()
{register object *base=vs_base;
	register object *sup=base+VM20; VC20
	vs_check;
	{object V51;
	object V52;
	V51=(base[0]);
	V52=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object x= (V52),V54= (V51);
	while(V54!=Cnil)
	if(eql(x,V54->c.c_car->c.c_car) &&V54->c.c_car != Cnil){
	V53= (V54->c.c_car);
	goto T141;
	}else V54=V54->c.c_cdr;
	V53= Cnil;}
	goto T141;
T141:;
	base[2]= CMPcdr(V53);
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
