L16()
{register object *VOL base=vs_base;
	register object *VOL sup=base+VM16; VC16
	vs_check;
	bds_check;
	vs_top=sup;
	goto TTL;
TTL:;
	vs_base=vs_top;
	(void) (*Lnk170)();
	vs_top=sup;
	V25= vs_base[0];
	base[3]= immnum_mod(V25,((object)VV[66]));
	bds_bind(((object)VV[62]),small_fixnum(10));
	bds_bind(((object)VV[63]),small_fixnum(10));
	bds_bind(((object)VV[64]),Ct);
	bds_bind(((object)VV[65]),base[3]);
	(((object)VV[67])->s.s_dbind)= Ct;
	vs_base=vs_top;
	(void) (*Lnk171)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk172)();
	vs_top=sup;{VOL object V26;
	V26= (((object)VV[68])->s.s_dbind);
	(((object)VV[68])->s.s_dbind)= immnum_plus(V26,immnum_mod((((object)VV[65])->s.s_dbind),small_fixnum(100)));}
	vs_base=vs_top;
	(void) (*Lnk173)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk174)();
	vs_top=sup;
	frs_push(FRS_CATCH,((object)VV[69]));
	if(nlj_active)
	{nlj_active=FALSE;frs_pop();
	vs_top=sup;
	goto T123;}
	else{
	vs_base=vs_top;
	(void) (*Lnk175)();
	vs_top=sup;
	frs_pop();}
	goto T123;
T123:;
	vs_base=vs_top;
	(void) (*Lnk176)();
	bds_unwind1;
	bds_unwind1;
	bds_unwind1;
	bds_unwind1;
	return;
}
