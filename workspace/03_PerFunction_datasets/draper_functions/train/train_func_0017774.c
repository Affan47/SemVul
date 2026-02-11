L166()
{register object *base=vs_base;
	register object *sup=base+VM166; VC166
	vs_check;
	{object V1068;
	object V1069;
	object V1070;
	object V1071;
	object V1072;
	V1068=(base[0]);
	V1069=(base[1]);
	V1070=(base[2]);
	V1071=(base[3]);
	V1072=(base[4]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[5]= (V1068);
	base[6]= CMPcar((V1071));
	base[7]= CMPcadr((V1071));
	base[8]= (V1072);
	V1073= immnum_minus((V1070),CMPcadr((V1071)));
	base[9]= immnum_abs(V1073);
	vs_top=(vs_base=base+5)+5;
	(void) (*Lnk335)();
	return;
	}
}
