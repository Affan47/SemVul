L49()
{register object *base=vs_base;
	register object *sup=base+VM49; VC49
	vs_check;
	{object V168;
	V168=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!(((((object)VV[29])->s.s_dbind))==(((object)VV[129])))){
	goto T588;}
	vs_base=vs_top;
	(void) (*Lnk166)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk194)();
	vs_top=sup;
	base[2]= vs_base[0];
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk195)();
	vs_top=sup;
	base[1]= vs_base[0];
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk196)();
	vs_top=sup;
	V169= vs_base[0];
	base[1]= list(3,((object)VV[130]),(V168),V169);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T588;
T588:;
	base[1]= (V168);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
