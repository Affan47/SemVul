L2()
{register object *base=vs_base;
	register object *sup=base+VM2; VC2
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	{object V3;
	V3= Cnil;
	{object V4;
	vs_base=vs_top;
	(void) (*Lnk5)();
	vs_top=sup;
	base[0]= vs_base[0];
	base[1]= (*(LnkLI6))(((object)VV[1]),((object)VV[2]),Cnil,Cnil,Cnil);
	vs_top=(vs_base=base+0)+2;
	(void) (*Lnk7)();
	vs_top=sup;
	V3= vs_base[0];
	V4= (V3);
	(void)(elt_set((V3),(long)0,((object)VV[3])));
	base[0]= (V4);
	vs_top=(vs_base=base+0)+1;
	return;}
	base[0]= Cnil;
	vs_top=(vs_base=base+0)+1;
	return;}
}
