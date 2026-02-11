L6()
{register object *base=vs_base;
	register object *sup=base+VM6; VC6
	vs_check;
	{object V29;
	object V30;
	V29=(base[0]);
	V30=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(immnum_lt((V30),small_fixnum(1))){
	goto T88;}
	if((CMPcar((V29)))==(((object)VV[15]))){
	goto T89;}
	goto T88;
T88:;
	base[2]= make_cons(Cnil,(V29));
	vs_top=(vs_base=base+2)+1;
	return;
	goto T89;
T89:;
	{object V31;
	V31= CMPcdr((V29));
	{object V32;
	object V33;
	V32= CMPcar((V31));
	V33= CMPcadr((V31));
	{object V34;
	base[2]= (V33);
	base[3]= immnum_minus((V30),small_fixnum(1));
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk135)();
	vs_top=sup;
	V34= vs_base[0];
	V35= make_cons((V32),CMPcar((V34)));
	base[2]= make_cons(V35,CMPcdr((V34)));
	vs_top=(vs_base=base+2)+1;
	return;}}}
	}
}
