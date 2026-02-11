L65()
{register object *base=vs_base;
	register object *sup=base+VM65; VC65
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	(((object)VV[76])->s.s_dbind)= Cnil;
	base[0]= small_fixnum(3);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk88)();
	vs_top=sup;
	base[0]= Cnil;
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk96)();
	return;
}
