L3__C2BLOCK__cmpblock()
{register object *base=vs_base;
	register object *sup=base+VM3; VC3
	vs_check;
	{register object V16;
	object V17;
	V16=(base[0]);
	V17=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	if((STREF(object,(V16),24))==Cnil){
	goto T32;}
	base[2]= (*(LnkLI31))((V16),(V17));
	vs_top=(vs_base=base+2)+1;
	return;
	goto T32;
T32:;
	if((STREF(object,(V16),16))==Cnil){
	goto T35;}
	base[2]= (*(LnkLI32))((V16),(V17));
	vs_top=(vs_base=base+2)+1;
	return;
	goto T35;
T35:;
	base[2]= (V16);
	base[3]= (V17);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk33)();
	return;
	}
}
