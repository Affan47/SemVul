L128()
{register object *base=vs_base;
	register object *sup=base+VM128; VC128
	vs_check;
	{object V741;
	object V742;
	object V743;
	V741=(base[0]);
	V742=(base[1]);
	V743=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V744;
	V744= Cnil;
	{register object x= (V742),V745= ({register fixnum _i=(long)13;register object _x=(V741);for (;_i--;_x=_x->c.c_cdr);_x->c.c_car;});
	while(V745!=Cnil)
	if(eql(x,V745->c.c_car->c.c_car) &&V745->c.c_car != Cnil){
	V744= (V745->c.c_car);
	goto T2907;
	}else V745=V745->c.c_cdr;
	V744= Cnil;}
	goto T2907;
T2907:;
	if(((V744))==Cnil){
	goto T2905;}
	(CMPcdr(V744))->c.c_car = V743;
	(void)(CMPcdr(V744));
	base[3]= V743;
	vs_top=(vs_base=base+3)+1;
	return;
	goto T2905;
T2905:;
	{object V748;
	object V751;
	V748= list(2,(V742),(V743));
	V752= (*(LnkLI271))(small_fixnum(13),V741);
	V751= make_cons((V748),V752);
	V753= (*(LnkLI273))(small_fixnum(13),V741);
	(V753)->c.c_car = (V751);
	base[3]= (V751);
	vs_top=(vs_base=base+3)+1;
	return;}}
	}
}
