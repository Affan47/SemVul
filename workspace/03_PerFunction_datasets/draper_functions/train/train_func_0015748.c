L39()
{register object *base=vs_base;
	register object *sup=base+VM39; VC39
	vs_check;
	{object V245;
	object V246;
	V245=(base[0]);
	V246=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((V246))!=Cnil){
	goto T985;}
	base[2]= (V245);
	base[3]= (((object)VV[74])->s.s_dbind);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk235)();
	return;
	goto T985;
T985:;
	{object V247;
	base[2]= (V245);
	base[3]= CMPcar((V246));
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk235)();
	vs_top=sup;
	V247= vs_base[0];
	if(((V247))==Cnil){
	goto T993;}
	base[2]= (V247);
	vs_top=(vs_base=base+2)+1;
	return;
	goto T993;
T993:;
	V246= CMPcdr((V246));
	goto TTL;}
	}
}
