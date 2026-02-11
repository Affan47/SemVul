L106()
{register object *base=vs_base;
	register object *sup=base+VM106; VC106
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	{object V462;
	register object V463;
	object V464;
	V462= Cnil;
	V463= Cnil;
	V464= Cnil;
	V462= ((object)VV[67]);
	V463= (VFUN_NARGS=1,(*(LnkLI85))(small_fixnum(138),small_fixnum(0)));
	(void)(((V463))->v.v_self[(long)0]= ((V462)));
	V464= (*(LnkLI86))(small_fixnum(0),small_fixnum(0),Cnil);
	(void)(((V463))->v.v_self[(long)3]= ((V464)));{object V465;
	V465= (((object)VV[66])->s.s_dbind);
	V466= make_cons(small_fixnum(1),(V463));
	(void)((*(LnkLI87))(V465,((object)VV[65]),Cnil,V466));}
	(void)((*(LnkLI88))((V463)));
	base[0]= (V463);
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk89)();
	vs_top=sup;
	V467= vs_base[0];
	(void)(((V463))->v.v_self[(long)6]= (V467));
	base[0]= (V463);
	vs_top=(vs_base=base+0)+1;
	return;
	base[0]= Cnil;
	vs_top=(vs_base=base+0)+1;
	return;}
}
