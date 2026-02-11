L70()
{register object *base=vs_base;
	register object *sup=base+VM70; VC70
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	base[0]= small_fixnum(0);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk97)();
	vs_top=sup;
	(((object)VV[79])->s.s_dbind)= Cnil;
	(((object)VV[80])->s.s_dbind)= Ct;
	(((object)VV[81])->s.s_dbind)= Ct;
	base[0]= Cnil;
	vs_top=(vs_base=base+0)+1;
	return;
}
