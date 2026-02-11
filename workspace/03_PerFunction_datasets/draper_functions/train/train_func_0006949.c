L206()
{register object *base=vs_base;
	register object *sup=base+VM206; VC206
	vs_check;
	{object V1516;
	V1516=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (V1516);
	vs_top=(vs_base=base+1)+1;
	Lalpha_char_p();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T5382;}
	base[1]= Ct;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T5382;
T5382:;
	base[1]= (V1516);
	vs_top=(vs_base=base+1)+1;
	Ldigit_char_p();
	vs_top=sup;
	V1517= vs_base[0];
	base[1]= ((((V1517)==Cnil?Ct:Cnil))==Cnil?Ct:Cnil);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
