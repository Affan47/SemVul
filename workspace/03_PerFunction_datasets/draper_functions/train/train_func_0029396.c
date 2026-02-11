L32()
{register object *base=vs_base;
	register object *sup=base+VM32; VC32
	vs_check;
	{object V219;
	V219=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V220;
	base[3]= CMPcar((V219));
	vs_top=(vs_base=base+3)+1;
	(void) (*Lnk174)();
	vs_top=sup;
	base[2]= vs_base[0];
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk129)();
	vs_top=sup;
	base[1]= vs_base[0];
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk175)();
	vs_top=sup;
	V220= vs_base[0];
	base[1]= CMPcdr((V219));
	base[2]= make_cons((V220),Cnil);
	base[3]= (V220);
	vs_top=(vs_base=base+1)+3;
	(void) (*Lnk148)();
	vs_top=sup;
	(CMPcar((((object)VV[31])->s.s_dbind)))->c.c_car = ((object)VV[32]);
	(void)(CMPcar((((object)VV[31])->s.s_dbind)));
	base[1]= (V220);
	vs_top=(vs_base=base+1)+1;
	return;}
	}
}
