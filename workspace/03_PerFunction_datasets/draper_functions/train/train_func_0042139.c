L2()
{register object *base=vs_base;
	register object *sup=base+VM2; VC2
	vs_check;
	{object V3;
	object V4;
	V3=(base[0]);
	V4=(base[1]);
	vs_top=sup;
	goto TTL;
TTL:;
	{register object x= (V3),V5= (V4);
	while(V5!=Cnil)
	if(equal(x,V5->c.c_car)){
	base[2]= V5;
	vs_top=(vs_base=base+2)+1;
	return;
	}else V5=V5->c.c_cdr;
	base[2]= Cnil;
	vs_top=(vs_base=base+2)+1;
	return;}
	}
}
