L1()
{register object *base=vs_base;
	register object *sup=base+VM1; VC1
	vs_check;
	{register object V1;
	V1=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!((CMPcar((V1)))==(((object)VV[0])))){
	goto T1;}
	base[1]= Ct;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T1;
T1:;{object V2;
	if((CMPcar((V1)))==(((object)VV[1]))){
	goto T5;}
	V2= Cnil;
	goto T4;
	goto T5;
T5:;
	base[1]= CMPcadr((V1));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk24)();
	vs_top=sup;
	V2= vs_base[0];
	goto T4;
T4:;
	if(V2==Cnil)goto T3;
	base[1]= V2;
	vs_top=(vs_base=base+1)+1;
	return;
	goto T3;
T3:;}
	base[1]= ((CMPcar((V1)))==(((object)VV[2]))?Ct:Cnil);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
