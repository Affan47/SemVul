L30()
{register object *base=vs_base;
	register object *sup=base+VM30; VC30
	vs_check;
	{object V379;
	object V380;
	V379=(base[0]);
	V380=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V381;
	object V382;
	register object V383;
	V381= Cnil;
	V382= Cnil;
	V383= Cnil;
	V381= Cnil;
	V382= Cnil;
	{object V384;
	V384= ((V380))->v.v_self[(long)28];
	V383= (
	V385 = CMPcar((V384)),
	(type_of(V385) == t_sfun ?(*((V385)->sfn.sfn_self)):
	(fcall.argd=2,type_of(V385)==t_vfun) ?
	(*((V385)->sfn.sfn_self)):
	(fcall.fun=(V385),fcalln))((V379),CMPcdr((V384))));}
	goto T1116;
T1116:;
	if(type_of((V383))!=t_cons){
	goto T1123;}
	V382= CMPcar((V383));
	goto T1122;
	goto T1123;
T1123:;
	goto T1117;
	goto T1122;
T1122:;
	{register object V387;
	V387= ((V380))->v.v_self[(long)23];
	base[2]= CMPcar((V387));
	base[3]= (V382);
	base[4]= CMPcdr((V387));
	vs_top=(vs_base=base+3)+2;
	super_funcall_no_event(base[2]);
	vs_top=sup;
	V386= vs_base[0];}
	V381= make_cons(V386,(V381));
	goto T1129;
	goto T1129;
T1129:;
	V383= CMPcdr((V383));
	goto T1116;
	goto T1117;
T1117:;
	base[2]= (*(LnkLI15))((V381));
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	}
}
