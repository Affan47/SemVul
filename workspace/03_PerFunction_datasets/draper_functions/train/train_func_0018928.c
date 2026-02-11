LC19(base0)
register object *base0;
{	register object *base=vs_base;
	register object *sup=base+VM20; VC20
	vs_check;
	{object V78;
	V78=(base[0]);
	vs_top=sup;
	base[1]= (V78);
	base[2]= ((object)VV[16]);
	base[3]= CMPcar((base0[2]->c.c_car));
	vs_top=(vs_base=base+1)+3;
	Lformat();
	return;
	}
}
