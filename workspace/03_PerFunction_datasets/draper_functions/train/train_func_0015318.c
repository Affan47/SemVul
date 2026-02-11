L8()
{register object *base=vs_base;
	register object *sup=base+VM8; VC8
	vs_check;
	{object V14;
	V14=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!(type_of((V14))!=t_cons)){
	goto T305;}
	base[1]= (V14);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk1)();
	return;
	goto T305;
T305:;
	if(!(immnum_zerop((((object)VV[5])->s.s_dbind)))){
	goto T309;}
	base[1]= ((object)VV[62]);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk1)();
	return;
	goto T309;
T309:;
	base[1]= (V14);
	base[2]= one_minus((((object)VV[5])->s.s_dbind));
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk78)();
	return;
	}
}
