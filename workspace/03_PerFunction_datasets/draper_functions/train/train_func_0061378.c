L22()
{register object *base=vs_base;
	register object *sup=base+VM22; VC22
	vs_check;
	{object V59;
	V59=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!(((((object)VV[32])->s.s_dbind))==(((object)VV[74])))){
	goto T185;}
	vs_base=vs_top;
	(void) (*Lnk92)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk99)();
	vs_top=sup;
	V60= vs_base[0];
	base[1]= list(4,((object)VV[75]),((object)VV[76]),(V59),V60);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T185;
T185:;
	base[1]= (V59);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
