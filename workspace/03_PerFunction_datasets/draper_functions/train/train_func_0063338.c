L9()
{register object *base=vs_base;
	register object *sup=base+VM9; VC9
	vs_check;
	{object V18;
	V18=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	V19= make_cons(CMPcadr((((object)VV[15])->s.s_dbind)),CMPcar((V18)));
	(((object)VV[14])->s.s_dbind)= make_cons(V19,(((object)VV[14])->s.s_dbind));
	base[1]= (V18);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
