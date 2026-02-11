L5()
{register object *base=vs_base;
	register object *sup=base+VM5; VC5
	vs_reserve(VM5);
	{object V37;
	object V38;
	object V39;
	object V40;
	object V41;
	object V42;
	object V43;
	object V44;
	object V45;
	object V46;
	object V47;
	object V48;
	if(vs_top-vs_base<1) too_few_arguments();
	parse_key(vs_base+1,TRUE,FALSE,10,VV[79],VV[80],VV[81],VV[82],VV[83],VV[84],VV[85],VV[86],VV[87],VV[88]);
	V37=(base[0]);vs_top=sup;
	V38=(base[1]);
	V39=(base[2]);
	V40=(base[3]);
	V41=(base[4]);
	V42=(base[5]);
	V43=(base[6]);
	V44=(base[7]);
	V45=(base[8]);
	V46=(base[9]);
	V47=(base[10]);
	V48=(base[11]);
	{object V49;
	vs_base=vs_top;
	(void) (*Lnk89)();
	vs_top=sup;
	V49= vs_base[0];
	base[22]= (V37);
	base[23]= ((object)VV[10]);
	base[24]= (V49);
	{object V50;
	V50= (V38);
	 vs_top=base+25;
	 while(!endp(V50))
	 {vs_push(car(V50));V50=cdr(V50);}
	vs_base=base+22;}
	Lwrite();
	vs_top=sup;
	base[22]= (V49);
	vs_top=(vs_base=base+22)+1;
	(void) (*Lnk9)();
	return;}
	}
}
