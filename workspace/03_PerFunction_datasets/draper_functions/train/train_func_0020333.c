L10()
{register object *base=vs_base;
	register object *sup=base+VM10; VC10
	vs_reserve(VM10);
	check_arg(0);
	vs_top=sup;
	goto TTL;
TTL:;
	base[0]= list(3,((object)VV[47]),((object)VV[0]),list(2,((object)VV[48]),((object)VV[51])));
	vs_top=(vs_base=base+0)+1;
	return;
}
