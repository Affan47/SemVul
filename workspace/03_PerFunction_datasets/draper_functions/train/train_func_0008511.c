L5()
{register object *base=vs_base;
	register object *sup=base+VM5; VC5
	vs_check;
	{object V12;
	object V13;
	object V14;
	V12=(base[0]);
	V13=(base[1]);
	V14=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	if((V12)==Cnil){
	goto T5;}
	base[3]= CMPcar(V12);
	vs_top=(vs_base=base+3)+1;
	return;
	goto T5;
T5:;
	base[3]= (*(LnkLI24))();
	vs_top=(vs_base=base+3)+1;
	return;
	}
}
