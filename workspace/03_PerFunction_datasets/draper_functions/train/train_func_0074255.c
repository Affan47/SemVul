L38()
{register object *base=vs_base;
	register object *sup=base+VM38; VC38
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	{object V142;
	V142= (((object)VV[29])->s.s_dbind);
	vs_base=vs_top;
	(void) (*Lnk166)();
	vs_top=sup;
	V143= vs_base[0];
	if((V143)==(((object)VV[60]))){
	goto T500;}
	base[0]= make_cons((V142),Cnil);
	vs_top=(vs_base=base+0)+1;
	return;
	goto T500;
T500:;
	vs_base=vs_top;
	(void) (*Lnk166)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk186)();
	vs_top=sup;
	V144= vs_base[0];
	base[0]= make_cons((V142),V144);
	vs_top=(vs_base=base+0)+1;
	return;}
}
