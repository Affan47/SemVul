L7()
{register object *base=vs_base;
	register object *sup=base+VM7; VC7
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	V21= make_cons(small_fixnum(-1),Cnil);
	(((object)VV[9])->s.s_dbind)= make_cons(V21,Cnil);
	base[0]= (((object)VV[9])->s.s_dbind);
	vs_top=(vs_base=base+0)+1;
	return;
}
