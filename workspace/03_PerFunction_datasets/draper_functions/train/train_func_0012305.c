L54()
{register object *base=vs_base;
	register object *sup=base+VM54; VC54
	vs_check;
	{object V94;
	V94=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	V95= symbol_name((V94));
	base[1]= code_char((V95)->ust.ust_self[(long)0]);
	vs_top=(vs_base=base+1)+1;
	Lchar_int();
	return;
	}
}
