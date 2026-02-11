L78()
{register object *base=vs_base;
	register object *sup=base+VM78; VC78
	vs_check;
	{object V245;
	object V246;
	V245=(base[0]);
	V246=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V247;
	V247= Cnil;
	base[2]= (V245);
	vs_top=(vs_base=base+2)+1;
	Ltruncate();
	vs_top=sup;
	V247= vs_base[0];
	base[2]= (V247);
	base[3]= ((object)VV[39]);
	vs_top=(vs_base=base+2)+2;
	Lfloat();
	vs_top=sup;
	V248= vs_base[0];
	if(!(immnum_eq((V245),V248))){
	goto T299;}
	base[2]= (V247);
	vs_top=(vs_base=base+2)+1;
	return;
	goto T299;
T299:;
	base[2]= (*(LnkLI66))(((object)VV[40]));
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	}
}
