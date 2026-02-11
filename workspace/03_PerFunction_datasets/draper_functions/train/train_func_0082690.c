L4()
{register object *base=vs_base;
	register object *sup=base+VM4; VC4
	vs_check;vs_top=sup;
	{object V8=base[0]->c.c_cdr;
	base[2]= (V8->c.c_car);
	V8=V8->c.c_cdr;
	base[3]= V8;}
	base[4]= list(3,((object)VV[4]),((object)VV[5]),listA(4,((object)VV[6]),base[2],((object)VV[7]),base[3]));
	vs_top=(vs_base=base+4)+1;
	return;
}
