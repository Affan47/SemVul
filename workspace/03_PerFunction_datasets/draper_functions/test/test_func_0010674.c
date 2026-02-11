L35__COMPILER_MACRO_FUNCTION__evalmacros()
{register object *base=vs_base;
	register object *sup=base+VM31; VC31
	vs_reserve(VM31);
	{object V232;
	check_arg(1);
	V232=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= get((V232),((object)VV[60]),Cnil);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
