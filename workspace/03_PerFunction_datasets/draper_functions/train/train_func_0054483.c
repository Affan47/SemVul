L26()
{register object *base=vs_base;
	register object *sup=base+VM26; VC26
	vs_check;vs_top=sup;
	{object V26=base[0]->c.c_cdr;
	base[2]= (V26->c.c_car);
	V26=V26->c.c_cdr;
	base[3]= (V26->c.c_car);
	V26=V26->c.c_cdr;
	base[4]= (V26->c.c_car);}
	base[5]= list(3,((object)VV[0]),((object)VV[15]),list(3,((object)VV[0]),list(3,((object)VV[0]),base[2],base[3]),base[4]));
	vs_top=(vs_base=base+5)+1;
	return;
}
