LC223(base0)
register object *base0;
{	register object *base=vs_base;
	register object *sup=base+VM221; VC221
	vs_check;
	{object V1648;
	object V1649;
	object V1650;
	V1648=(base[0]);
	V1649=(base[1]);
	V1650=(base[2]);
	vs_top=sup;
	if(immnum_zerop((V1650))){
	goto T5827;}
	(base0[0]->c.c_car)= (V1650);
	(base0[2]->c.c_car)= (V1648);
	(base0[1]->c.c_car)= (V1649);
	base[3]= (base0[1]->c.c_car);
	vs_top=(vs_base=base+3)+1;
	return;
	goto T5827;
T5827:;
	base[3]= Cnil;
	vs_top=(vs_base=base+3)+1;
	return;
	}
}
