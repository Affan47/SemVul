L46()
{register object *base=vs_base;
	register object *sup=base+VM46; VC46
	vs_check;
	{object V169;
	V169=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V170;
	base[1]= (V169);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk154)();
	vs_top=sup;
	V170= vs_base[0];
	if(!(((long)1)<((long)length((V170))))){
	goto T537;}
	{frame_ptr fr;
	fr=frs_sch_catch(((object)VV[113]));
	if(fr==NULL) FEerror("The tag ~s is undefined.",1,((object)VV[113]));
	base[1]= ((object)VV[121]);
	vs_top=(vs_base=base+1)+1;
	unwind(fr,((object)VV[113]));}
	goto T537;
T537:;
	base[1]= CMPcar((V170));
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk183)();
	return;}
	}
}
