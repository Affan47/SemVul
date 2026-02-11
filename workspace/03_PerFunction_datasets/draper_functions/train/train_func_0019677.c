L11()
{register object *base=vs_base;
	register object *sup=base+VM11; VC11
	vs_check;
	{object V39;
	V39=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;{object V40;
	{object V41 =((V39))->s.s_plist;
	 object ind= ((object)VV[53]);
	while(V41!=Cnil){
	if(V41->c.c_car==ind){
	V40= (V41->c.c_cdr->c.c_car);
	goto T113;
	}else V41=V41->c.c_cdr->c.c_cdr;}
	V40= Cnil;}
	goto T113;
T113:;
	if(V40==Cnil)goto T112;
	base[1]= V40;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T112;
T112:;}
	base[2]= ((object)VV[54]);
	base[3]= (V39);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk149)();
	vs_top=sup;
	base[1]= vs_base[0];
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk145)();
	return;
	}
}
