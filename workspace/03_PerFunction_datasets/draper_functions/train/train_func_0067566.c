L4()
{register object *base=vs_base;
	register object *sup=base+VM4; VC4
	vs_check;
	{object V22;
	V22=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V23;
	object V24;
	register object V25;
	object V26;
	V23= Cnil;
	V24= Cnil;
	V25= Cnil;
	V26= Cnil;
	V23= (*(LnkLI3))((V22));
	V24= list(2,((object)VV[1]),(V23));
	V25= (VFUN_NARGS=1,(*(LnkLI4))(small_fixnum(27),small_fixnum(0)));
	(void)(((V25))->v.v_self[(long)0]= ((V24)));
	V26= (*(LnkLI5))(small_fixnum(0),small_fixnum(0),Cnil);
	(void)(((V25))->v.v_self[(long)3]= ((V26)));
	(void)((*(LnkLI6))((V25)));
	(void)(((V25))->v.v_self[(long)6]= ((V22)));
	base[1]= (V25);
	vs_top=(vs_base=base+1)+1;
	return;
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;}
	}
}
