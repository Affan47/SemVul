L6()
{register object *base=vs_base;
	register object *sup=base+VM6; VC6
	vs_check;
	{register object V11;
	if(vs_base>=vs_top){vs_top=sup;goto T18;}
	V11=(base[0]);
	vs_top=sup;
	goto T19;
	goto T18;
T18:;
	V11= (((object)VV[3])->s.s_dbind);
	goto T19;
T19:;
	{register object V12;
	V12= (((object)VV[2])->s.s_dbind);
	goto T22;
T22:;
	if((CMPcdr((V12)))!=Cnil){
	goto T23;}
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T23;
T23:;
	{object V14=
	CMPcadr((V12))
	->c.c_cdr;
	V13= (V14->c.c_car);}
	if(!(equal(V13,(V11)))){
	goto T27;}
	{register object V16;
	V16= CMPcddr((V12));
	(V12)->c.c_cdr = SAFE_CDR((V16));}
	base[1]= (V11);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T27;
T27:;
	V12= CMPcdr((V12));
	goto T22;}
	}
}
