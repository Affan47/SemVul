L3()
{register object *base=vs_base;
	register object *sup=base+VM3; VC3
	vs_check;
	{object V6;
	V6=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	V7= (*(LnkLI77))((V6),(((object)VV[4])->s.s_dbind));
	base[1]= CMPcar(V7);
	base[2]= (((object)VV[5])->s.s_dbind);
	vs_top=(vs_base=base+1)+2;
	(void) (*Lnk78)();
	return;
	}
}
