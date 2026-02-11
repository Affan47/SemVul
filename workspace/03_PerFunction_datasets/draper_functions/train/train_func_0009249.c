L77()
{register object *base=vs_base;
	register object *sup=base+VM77; VC77
	vs_check;
	{object V311;
	register object V312;
	V311=(base[0]);
	V312=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (V312);
	base[3]= small_fixnum(9);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk227)();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T918;}
	base[2]= (V312);
	base[3]= (((object)VV[106])->s.s_dbind);
	vs_top=(vs_base=base+2)+2;
	(void) (*Lnk228)();
	vs_top=sup;
	if((vs_base[0])!=Cnil){
	goto T918;}
	{object V313;
	base[2]= (V311);
	base[3]= ((object)VV[130]);
	base[4]= (((object)VV[123])->s.s_dbind);
	vs_top=(vs_base=base+2)+3;
	(void) (*Lnk143)();
	vs_top=sup;
	V313= vs_base[0];
	(((object)VV[123])->s.s_dbind)= immnum_plus((((object)VV[123])->s.s_dbind),small_fixnum(1));
	{object V314;
	V314= make_cons((V313),(V312));
	(((object)VV[106])->s.s_dbind)= make_cons((V314),(((object)VV[106])->s.s_dbind));}}
	goto T918;
T918:;
	base[2]= (V312);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk229)();
	return;
	}
}
