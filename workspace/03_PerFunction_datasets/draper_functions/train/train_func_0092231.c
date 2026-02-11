L32()
{register object *base=vs_base;
	register object *sup=base+VM32; VC32
	vs_check;
	{object V61;
	V61=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[2]= (V61);
	base[1]= simple_symlispcall(((object)VV[82]),base+2,1);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk67)();
	vs_top=sup;
	V62= vs_base[0];
	base[1]= listA(3,((object)VV[27]),(V61),V62);
	vs_top=(vs_base=base+1)+1;
	return;
	}
}
