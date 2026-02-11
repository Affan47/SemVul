L22()
{register object *base=vs_base;
	register object *sup=base+VM22; VC22
	vs_check;
	{register object V172;
	V172=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if((CMPcar((V172)))==(((object)VV[21]))){
	goto T510;}
	goto T508;
	goto T510;
T510:;
	if(!((CMPcadr((V172)))==(Cnil))){
	goto T508;}
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T508;
T508:;
	base[1]= CMPcdadr(CMPcaadr((V172)));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk121)();
	vs_top=sup;
	V173= vs_base[0];
	base[1]= CMPcdadr((V172));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk170)();
	vs_top=sup;
	V174= vs_base[0];
	base[1]= make_cons(V173,V174);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
