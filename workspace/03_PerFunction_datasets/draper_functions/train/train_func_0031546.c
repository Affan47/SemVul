L127__PICMENU_DRAW_NAMED_BUTTON__dwtrans()
{register object *base=vs_base;
	register object *sup=base+VM127; VC127
	vs_check;
	{object V738;
	object V739;
	V738=(base[0]);
	V739=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (V738);
	{register object x= (V739),V740= CMPcadddr(({register fixnum _i=(long)10;register object _x=(V738);for (;_i--;_x=_x->c.c_cdr);_x->c.c_car;}));
	while(V740!=Cnil)
	if(eql(x,V740->c.c_car->c.c_car) &&V740->c.c_car != Cnil){
	base[3]= (V740->c.c_car);
	goto T2903;
	}else V740=V740->c.c_cdr;
	base[3]= Cnil;}
	goto T2903;
T2903:;
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk308)();
	return;
	}
}
