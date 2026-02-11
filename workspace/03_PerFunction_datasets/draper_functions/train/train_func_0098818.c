L64()
{register object *base=vs_base;
	register object *sup=base+VM64; VC64
	vs_check;
	{object V327;
	object V328;
	object V329;
	V327=(base[0]);
	V328=(base[1]);
	V329=(base[2]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V330;
	base[3]= (V328);
	vs_top=(vs_base=base+3)+1;
	(void) (*Lnk184)();
	vs_top=sup;
	V330= vs_base[0];
	base[3]= (((object)VV[5])->s.s_dbind);
	base[4]= CMPcadr((V327));
	base[5]= CMPcaddr((V327));
	base[6]= CMPcar((V329));
	base[7]= immnum_minus(CMPcadddr((V327)),CMPcadr((V329)));
	base[9]= (V330);
	vs_top=(vs_base=base+9)+1;
	(void) (*Lnk163)();
	vs_top=sup;
	base[8]= vs_base[0];
	base[9]= CMPmake_fixnum((long)(length((V330))));
	vs_top=(vs_base=base+3)+7;
	(void) (*Lnk235)();
	return;}
	}
}
