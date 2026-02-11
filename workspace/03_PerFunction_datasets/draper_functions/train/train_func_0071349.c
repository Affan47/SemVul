LC18__CLOSURE__clcs_top_patches(base0)
register object *base0;
{	register object *base=vs_base;
	register object *sup=base+VM15; VC15
	vs_check;
	{object V56;
	V56=(base[0]);
	vs_top=sup;
	base[1]= (V56);
	base[2]= ((object)VV[54]);
	base[3]= (base0[2]->c.c_car);
	vs_top=(vs_base=base+1)+3;
	Lformat();
	return;
	}
}
