L167()
{register object *base=vs_base;
	register object *sup=base+VM167; VC167
	vs_check;
	{object V1074;
	object V1075;
	object V1076;
	register object V1077;
	object V1078;
	V1074=(base[0]);
	V1075=(base[1]);
	V1076=(base[2]);
	V1077=(base[3]);
	V1078=(base[4]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V1079;
	object V1080;
	object V1081;
	V1079= Cnil;
	V1080= Cnil;
	V1081= Cnil;
	V1080= immnum_minus((V1076),CMPcadr((V1077)));
	V1079= immnum_minus((V1075),CMPcar((V1077)));
	if(immnum_ne((V1079),small_fixnum(0))){
	goto T4173;}
	if(!(immnum_ne((V1080),small_fixnum(0)))){
	goto T4174;}
	goto T4173;
T4173:;
	base[5]= immnum_minus((V1076),CMPcadr((V1077)));
	base[6]= immnum_minus((V1075),CMPcar((V1077)));
	vs_top=(vs_base=base+5)+2;
	Latan();
	vs_top=sup;
	V1081= vs_base[0];
	base[5]= (V1074);
	base[6]= CMPcar((V1077));
	base[7]= CMPcadr((V1077));
	V1082= CMPcar((V1077));
	base[9]= (V1081);
	vs_top=(vs_base=base+9)+1;
	Lcos();
	vs_top=sup;
	V1083= vs_base[0];
	V1084= immnum_times((V1078),V1083);
	base[8]= immnum_plus(V1082,V1084);
	V1085= CMPcadr((V1077));
	base[10]= (V1081);
	vs_top=(vs_base=base+10)+1;
	Lsin();
	vs_top=sup;
	V1086= vs_base[0];
	V1087= immnum_times((V1078),V1086);
	base[9]= immnum_plus(V1085,V1087);
	vs_top=(vs_base=base+5)+5;
	(void) (*Lnk219)();
	return;
	goto T4174;
T4174:;
	base[5]= Cnil;
	vs_top=(vs_base=base+5)+1;
	return;}
	}
}
