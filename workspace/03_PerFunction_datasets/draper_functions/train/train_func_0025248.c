L12()
{register object *base=vs_base;
	register object *sup=base+VM12; VC12
	vs_check;vs_top=sup;
	{object V44=base[0]->c.c_cdr;
	{object V45= (V44->c.c_car);
	base[2]= (V45->c.c_car);
	V45=V45->c.c_cdr;
	base[3]= (V45->c.c_car);
	V45=V45->c.c_cdr;
	if(endp(V45)){
	base[4]= Cnil;
	} else {
	base[4]= (V45->c.c_car);}}
	V44=V44->c.c_cdr;
	base[5]= V44;}
	{register object V46;
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V46= vs_base[0];
	V47= list(3,(V46),base[3],list(2,((object)VV[26]),(V46)));
	V48= list(2,((object)VV[27]),(V46));
	V49= list(2,V47,list(3,base[2],V48,list(2,((object)VV[27]),(V46))));
	V50= list(2,list(2,((object)VV[28]),(V46)),base[4]);
	base[6]= listA(5,((object)VV[25]),V49,V50,list(2,((object)VV[29]),list(3,((object)VV[30]),(V46),base[2])),base[5]);
	vs_top=(vs_base=base+6)+1;
	return;}
}
