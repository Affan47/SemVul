L57()
{register object *base=vs_base;
	register object *sup=base+VM57; VC57
	vs_check;
	{object V97;
	V97=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(((((object)VV[68])->s.s_dbind))==Cnil){
	goto T116;}
	base[1]= (V97);
	base[2]= (((object)VV[67])->s.s_dbind);
	vs_top=(vs_base=base+1)+2;
	Lpprint();
	return;
	goto T116;
T116:;
	base[1]= print((V97),(((object)VV[67])->s.s_dbind));
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
