L1__TRACE__trace()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;vs_top=sup;
	{object V1=base[0]->c.c_cdr;
	base[2]= V1;}
	if((base[2])!=Cnil){
	goto T2;}
	base[3]= ((object)VV[0]);
	vs_top=(vs_base=base+3)+1;
	return;
	goto T2;
T2:;
	base[3]= list(3,((object)VV[1]),((object)VV[2]),list(3,((object)VV[3]),list(3,((object)VV[4]),list(3,((object)VV[5]),((object)VV[6]),list(2,((object)VV[7]),base[2])),((object)VV[8])),((object)VV[9])));
	vs_top=(vs_base=base+3)+1;
	return;
}
