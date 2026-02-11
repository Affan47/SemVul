L8()
{register object *base=vs_base;
	register object *sup=base+VM8; VC8
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	if(((((object)VV[3])->s.s_dbind))==(((object)VV[9]))){
	goto T15;}
	base[0]= ((object)VV[10]);
	vs_top=(vs_base=base+0)+1;
	return;
	goto T15;
T15:;
	base[0]= Cnil;
	vs_top=(vs_base=base+0)+1;
	return;
}
