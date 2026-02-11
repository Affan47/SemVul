L35__MUFFLE_WARNING__clcs_restart()
{register object *base=vs_base;
	register object *sup=base+VM33; VC33
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	base[0]= ((object)VV[67]);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk79)();
	return;
}
