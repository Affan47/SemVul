L11()
{register object *base=vs_base;
	register object *sup=base+VM11; VC11
	vs_check;
	{object V20;
	V20=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	(void)(princ((V20),Cnil));
	vs_base=vs_top;
	Lfinish_output();
	vs_top=sup;
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
