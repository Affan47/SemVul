L7()
{register object *base=vs_base;
	register object *sup=base+VM7; VC7
	vs_reserve(VM7);
	{object V16;
	if(vs_top-vs_base>1) too_many_arguments();
	if(vs_base>=vs_top){vs_top=sup;goto T45;}
	V16=(base[0]);
	vs_top=sup;
	goto T46;
	goto T45;
T45:;
	V16= ((object)VV[19]);
	goto T46;
T46:;
	if(!(((V16))==(((object)VV[19])))){
	goto T49;}
	base[1]= ((object)VV[20]);
	vs_top=(vs_base=base+1)+1;
	return;
	goto T49;
T49:;
	V17= one_minus((V16));
	V18= number_expt(small_fixnum(2),V17);
	V19= immnum_negate(V18);
	V20= one_minus((V16));
	V21= number_expt(small_fixnum(2),V20);
	base[1]= list(3,((object)VV[15]),V19,one_minus(V21));
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
