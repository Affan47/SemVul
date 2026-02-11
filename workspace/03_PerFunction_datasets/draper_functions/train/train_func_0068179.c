L5()
{register object *base=vs_base;
	register object *sup=base+VM5; VC5
	vs_check;
	{object V11;
	V11=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	base[1]= (V11);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk146)();
	vs_top=sup;
	vs_base=vs_top;
	(void) (*Lnk147)();
	vs_top=sup;
	{frame_ptr fr;
	fr=frs_sch_catch(((object)VV[8]));
	if(fr==NULL) FEerror("The tag ~s is undefined.",1,((object)VV[8]));
	base[1]= Cnil;
	vs_top=(vs_base=base+1)+1;
	unwind(fr,((object)VV[8]));}
	}
}
