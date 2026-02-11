L47()
{register object *base=vs_base;
	register object *sup=base+VM47; VC47
	vs_check;
	{object V264;
	V264=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((((object)VV[107])->s.s_dbind))==Cnil){
	goto T1044;}
	base[1]= (V264);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T1044;
T1044:;
	if(!(type_of(CMPcdr((V264)))!=t_cons)){
	goto T1047;}
	base[1]= (V264);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T1047;
T1047:;
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
