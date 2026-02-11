L5()
{register object *base=vs_base;
	register object *sup=base+VM5; VC5
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	base[0]= (((((object)VV[8])->s.s_dbind))==(((object)VV[10]))?Ct:Cnil);
	vs_top=(vs_base=base+0)+1;
	return;
}
