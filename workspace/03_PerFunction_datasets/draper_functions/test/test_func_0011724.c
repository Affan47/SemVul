L31()
{register object *base=vs_base;
	register object *sup=base+VM31; VC31
	vs_check;
	{object V99;
	V99=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!(immnum_zerop((V99)))){
	goto T393;}
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T393;
T393:;
	base[1]= one_minus((V99));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk176)();
	vs_top=sup;
	V100= vs_base[0];
	base[1]= make_cons(small_fixnum(48),V100);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
