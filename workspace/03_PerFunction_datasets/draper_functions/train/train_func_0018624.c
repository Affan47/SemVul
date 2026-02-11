L7()
{register object *base=vs_base;
	register object *sup=base+VM7; VC7
	vs_check;
	{object V13;
	V13=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!((CMPcar((V13)))==(((object)VV[18])))){
	goto T6;}
	base[1]= Ct;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T6;
T6:;
	if((CMPcar((V13)))==(((object)VV[19]))){
	goto T8;}
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T8;
T8:;
	V13= CMPcadr((V13));
	goto TTL;
	}
}
