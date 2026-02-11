L24()
{register object *base=vs_base;
	register object *sup=base+VM24; VC24
	vs_check;
	{register object V157;
	V157=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((V157))==Cnil){
	goto T554;}
	if(!(type_of((V157))!=t_cons)){
	goto T557;}
	base[1]= ((object)VV[72]);
	base[2]= (((object)VV[73])->s.s_dbind);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk196)();
	return;
	goto T557;
T557:;
	base[1]= CMPcar((V157));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk206)();
	vs_top=sup;
	V158= vs_base[0];
	base[1]= CMPcdr((V157));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk206)();
	vs_top=sup;
	V159= vs_base[0];
	base[1]= make_cons(V158,V159);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T554;
T554:;
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
