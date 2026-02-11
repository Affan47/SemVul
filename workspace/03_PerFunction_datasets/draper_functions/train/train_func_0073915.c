L153__WINDOW_GET_BOX_POSITION__dwtrans()
{register object *base=vs_base;
	register object *sup=base+VM153; VC153
	vs_check;
	{object V969;
	object V970;
	object V971;
	object V972;
	object V973;
	V969=(base[0]);
	V970=(base[1]);
	V971=(base[2]);
	vs_base=vs_base+3;
	if(vs_base>=vs_top){vs_top=sup;goto T3909;}
	V972=(base[3]);
	vs_base++;
	if(vs_base>=vs_top){vs_top=sup;goto T3910;}
	V973=(base[4]);
	vs_top=sup;
	goto T3911;
	goto T3909;
T3909:;
	V972= small_fixnum(0);
	goto T3910;
T3910:;
	V973= small_fixnum(0);
	goto T3911;
T3911:;
	base[5]= (V969);
	base[6]= (((object)VV[224])->s.s_gfdef);
	base[7]= list(3,(V970),(V971),small_fixnum(1));
	base[8]= (V972);
	base[9]= (V973);
	vs_top=(vs_base=base+5)+5;
	(void) (*Lnk320)();
	return;
	}
}
