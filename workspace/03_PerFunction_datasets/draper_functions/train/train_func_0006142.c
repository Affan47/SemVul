L45()
{register object *base=vs_base;
	register object *sup=base+VM45; VC45
	vs_check;
	{object V144;
	object V145;
	V144=(base[0]);
	V145=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object V146;
	base[2]= (V145);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk195)();
	vs_top=sup;
	V147= vs_base[0];
	V146= CMPcar(V147);
	{register object V148;
	register object V149;
	V148= Cnil;
	V149= Cnil;
	base[2]= (V144);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk195)();
	vs_top=sup;
	V150= vs_base[0];
	V148= reverse(V150);
	V149= Cnil;
	goto T666;
T666:;
	if(((V148))!=Cnil){
	goto T672;}
	base[2]= ((object)VV[148]);
	vs_top=(vs_base=base+2)+1;
	return;
	goto T672;
T672:;
	if(((V149))==Cnil){
	goto T677;}
	if(!(immnum_eq(CMPcar((V148)),(V146)))){
	goto T680;}
	base[2]= reverse(CMPcdr((V148)));
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk222)();
	return;
	goto T680;
T680:;
	V148= CMPcdr((V148));
	goto T666;
	goto T677;
T677:;
	if(!(immnum_eq(CMPcar((V148)),(V146)))){
	goto T686;}
	V149= Ct;
	V148= CMPcdr((V148));
	goto T666;
	goto T686;
T686:;
	V148= CMPcdr((V148));
	goto T666;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}}
	}
}
