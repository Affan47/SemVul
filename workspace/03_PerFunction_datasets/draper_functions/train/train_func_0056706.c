L36()
{register object *base=vs_base;
	register object *sup=base+VM36; VC36
	vs_check;
	{object V451;
	object V452;
	V451=(base[0]);
	V452=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V453;
	V453= Cnil;
	{object V454;
	V454= ((V452))->v.v_self[(long)122];
	V453= (
	V455 = CMPcar((V454)),
	(type_of(V455) == t_sfun ?(*((V455)->sfn.sfn_self)):
	(fcall.argd=2,type_of(V455)==t_vfun) ?
	(*((V455)->sfn.sfn_self)):
	(fcall.fun=(V455),fcalln))((V451),CMPcdr((V454))));}
	if(!((fix(CMPcar((V453))))==((long)0))){
	goto T1338;}
	base[2]= CMPcdr((V453));
	vs_top=(vs_base=base+2)+1;
	return;
	goto T1338;
T1338:;
	base[2]= (*(LnkLI12))(((object)VV[7]));
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
