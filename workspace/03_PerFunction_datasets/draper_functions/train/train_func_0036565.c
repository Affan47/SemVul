L6()
{register object *base=vs_base;
	register object *sup=base+VM6; VC6
	vs_check;
	{object V19;
	V19=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V20;
	V20= CMPcadr((V19));
	(((object)VV[3])->s.s_dbind)= immnum_minus((((object)VV[3])->s.s_dbind),(V20));
	base[1]= (V20);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk33)();
	return;}
	}
}
