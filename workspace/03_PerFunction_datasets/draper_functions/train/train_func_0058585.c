L44()
{register object *base=vs_base;
	register object *sup=base+VM44; VC44
	vs_check;
	bds_check;
	{object V255;
	V255=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	bds_bind(((object)VV[6]),(((object)VV[5])->s.s_dbind));
	base[2]= (V255);
	vs_top=(vs_base=base+2)+1;
	(void) (*Lnk136)();
	bds_unwind1;
	return;
	}
}
