L49()
{register object *base=vs_base;
	register object *sup=base+VM49; VC49
	vs_check;
	{object V175;
	V175=(base[0]);
	vs_top=sup;
	goto TTL;
TTL:;
	{object V176;
	base[1]= (V175);
	vs_top=(vs_base=base+1)+1;
	(void) (*Lnk154)();
	vs_top=sup;
	V176= vs_base[0];
	if(!(((long)1)<((long)length((V176))))){
	goto T558;}
	{frame_ptr fr;
	fr=frs_sch_catch(((object)VV[113]));
	if(fr==NULL) FEerror("The tag ~s is undefined.",1,((object)VV[113]));
	base[1]= ((object)VV[125]);
	vs_top=(vs_base=base+1)+1;
	unwind(fr,((object)VV[113]));}
	goto T558;
T558:;
	(((object)VV[126])->s.s_dbind)= make_cons(CMPcar((V176)),(((object)VV[126])->s.s_dbind));
	base[1]= (((object)VV[126])->s.s_dbind);
	vs_top=(vs_base=base+1)+1;
	return;}
	}
}
