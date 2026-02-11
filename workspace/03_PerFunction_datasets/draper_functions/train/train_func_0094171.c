L11()
{register object *base=vs_base;
	register object *sup=base+VM11; VC11
	vs_check;vs_top=sup;
	{object V37=base[0]->c.c_cdr;
	{object V38= (V37->c.c_car);
	base[2]= (V38->c.c_car);
	V38=V38->c.c_cdr;
	base[3]= (V38->c.c_car);
	V38=V38->c.c_cdr;
	if(endp(V38)){
	base[4]= Cnil;
	} else {
	base[4]= (V38->c.c_car);}}
	V37=V37->c.c_cdr;
	base[5]= V37;}
	{register object V39;
	vs_base=vs_top;
	Lgensym();
	vs_top=sup;
	V39= vs_base[0];
	V40= list(3,(V39),base[3],list(2,((object)VV[26]),(V39)));
	V41= list(2,((object)VV[27]),(V39));
	V42= list(2,V40,list(3,base[2],V41,list(2,((object)VV[27]),(V39))));
	V43= list(2,list(2,((object)VV[28]),(V39)),base[4]);
	base[6]= listA(5,((object)VV[25]),V42,V43,list(2,((object)VV[29]),list(2,((object)VV[30]),base[2])),base[5]);
	vs_top=(vs_base=base+6)+1;
	return;}
}
