L1()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	(((object)VV[1])->s.s_dbind)= immnum_plus((((object)VV[1])->s.s_dbind),small_fixnum(1));
	base[0]= make_cons(((object)VV[0]),(((object)VV[1])->s.s_dbind));
	vs_top=(vs_base=base+0)+1;
	return;
}
