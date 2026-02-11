L7()
{register object *base=vs_base;
	register object *sup=base+VM7; VC7
	vs_check;
	{object V17;
	V17=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{
	object V18= (V17);
	if(V18==Cnil){
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;}
	goto T87;
T87:;
	{object V20;
	base[1]= CMPcdr((V18->c.c_car));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk30)();
	vs_top=sup;
	V20= vs_base[0];
	(void)(sputprop(CMPcar((V18->c.c_car)),((object)VV[4]),(V20)));
	{object V21;
	V21= CMPcar((V18->c.c_car));
	{object V23;
	base[1]= (((object)VV[5])->s.s_dbind);
	base[2]= V20;
	base[3]= (V21);
	vs_top=(vs_base=base+1)+3;
	siLput_f();
	vs_top=sup;
	V23= vs_base[0];
	(((object)VV[5])->s.s_dbind)= (V23);}}}
	if((V18=MMcdr(V18))==Cnil){
	base[1]= (V17);
	vs_top=(vs_base=base+1)+1;
	return;}
	goto T87;}
	}
}
