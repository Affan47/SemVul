L49()
{register object *base=vs_base;
	register object *sup=base+VM49; VC49
	vs_check;
	{object V153;
	V153=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	if(!((CMPcar((V153)))==(((object)VV[0])))){
	goto T321;}
	base[1]= CMPcddr(CMPcdr((V153)));
	vs_top=(vs_base=base+1)+1;
	return;
	goto T321;
T321:;
	base[1]= CMPcddr((V153));
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
