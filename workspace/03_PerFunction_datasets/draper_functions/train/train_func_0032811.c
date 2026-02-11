L26()
{register object *base=vs_base;
	register object *sup=base+VM26; VC26
	vs_check;
	{object V114;
	V114=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	(((object)VV[20])->s.s_dbind)= Cnil;
	base[1]= (V114);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk21)();
	return;
	}
}
