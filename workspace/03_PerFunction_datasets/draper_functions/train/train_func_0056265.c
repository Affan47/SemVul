L8__DO_ARRAY__cmpinline()
{register object *base=vs_base;
	register object *sup=base+VM8; VC8
	vs_check;vs_top=sup;
	{object V53=base[0]->c.c_cdr;
	{object V54= (V53->c.c_car);
	base[2]= (V54->c.c_car);
	V54=V54->c.c_cdr;
	base[3]= (V54->c.c_car);}
	V53=V53->c.c_cdr;
	base[4]= V53;}
	{register object V55;
	register object V56;
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V55= vs_base[0];
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V56= vs_base[0];
	V57= list(2,(V56),base[3]);
	V58= make_cons(V57,Cnil);
	V59= list(2,((object)VV[7]),list(2,((object)VV[8]),(V56)));
	V60= list(3,(V55),small_fixnum(0),list(2,((object)VV[10]),(V55)));
	V61= make_cons(V60,Cnil);
	V62= list(3,((object)VV[4]),(V55),list(2,((object)VV[11]),(V56)));
	V63= make_cons(V62,Cnil);
	V64= list(2,((object)VV[7]),list(2,((object)VV[12]),(V55)));
	V65= list(2,base[2],list(3,((object)VV[14]),(V56),(V55)));
	base[5]= list(4,((object)VV[6]),V58,V59,list(5,((object)VV[9]),V61,V63,V64,listA(3,((object)VV[13]),make_cons(V65,Cnil),base[4])));
	vs_top=(vs_base=base+5)+1;
	return;}
}
