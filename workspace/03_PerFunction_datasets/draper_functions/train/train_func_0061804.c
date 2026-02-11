L48()
{register object *base=vs_base;
	register object *sup=base+VM48; VC48
	vs_check;
	{object V166;
	V166=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!(((((object)VV[29])->s.s_dbind))==(((object)VV[127])))){
	goto T583;}
	vs_base=vs_top;
	(void) (*Lnk166)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk186)();
	vs_top=sup;
	V167= vs_base[0];
	base[1]= list(3,((object)VV[128]),(V166),V167);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T583;
T583:;
	base[1]= (V166);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
