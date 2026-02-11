L50()
{register object *base=vs_base;
	register object *sup=base+VM50; VC50
	vs_check;
	{object V182;
	object V183;
	V182=(base[0]);
	V183=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(immnum_lt(((object)VV[4]),(V182))){
	goto T138;}
	if(immnum_lt((V182),((object)VV[5]))){
	goto T138;}
	base[2]= (V182);
	vs_top=(vs_base=base+2)+1;
	return;
	goto T138;
T138:;
	base[2]= (*(LnkLI20))(((object)VV[6]));
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	}
}
