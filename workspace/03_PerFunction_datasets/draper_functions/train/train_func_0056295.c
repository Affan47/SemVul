L69()
{register object *base=vs_base;
	register object *sup=base+VM69; VC69
	vs_check;
	vs_top=sup;
	goto TTL;
TTL:;
	princ_str("Experimental version!",Cnil);
	princ_char(10,Cnil);
	base[0]= Ct;
	vs_top=(vs_base=base+0)+1;
	(void) (*Lnk96)();
	return;
}
