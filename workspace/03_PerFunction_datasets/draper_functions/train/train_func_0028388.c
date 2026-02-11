LI7(V39,V40)

register object V39;object V40;
{	 VMB7 VMS7 VMV7
	bds_check;
	goto TTL;
TTL:;
	{register object V41;
	bds_bind(((object)VV[3]),(((object)VV[3])->s.s_dbind));
	V41= Cnil;
	princ_str("\n	{frame_ptr fr;",((object)VV[6]));
	{object V42= CMPcar((V39));
	if((V42!= ((object)VV[35])))goto T117;
	V41= CMPcaddr((V39));
	goto T116;
	goto T117;
T117:;
	if((V42!= ((object)VV[22])))goto T119;
	V41= make_cons(((object)VV[22]),CMPcaddr((V39)));
	goto T116;
	goto T119;
T119:;
	V41= list(2,((object)VV[16]),(*(LnkLI32))());
	bds_bind(((object)VV[4]),(V41));
	V43= (*(LnkLI28))((V39));
	bds_unwind1;}
	goto T116;
T116:;
	princ_str("\n	fr=frs_sch_catch(",((object)VV[6]));
	(void)((*(LnkLI31))((V41)));
	princ_str(");",((object)VV[6]));
	princ_str("\n	if(fr==NULL) FEerror(\"The tag ~s is undefined.\",1,",((object)VV[6]));
	(void)((*(LnkLI31))((V41)));
	princ_str(");",((object)VV[6]));
	bds_bind(((object)VV[4]),((object)VV[17]));
	V44= (*(LnkLI28))((V40));
	bds_unwind1;
	princ_str("\n	unwind(fr,",((object)VV[6]));
	(void)((*(LnkLI31))((V41)));
	princ_str(");}",((object)VV[6]));
	{object V45 = Cnil;
	bds_unwind1;
	VMR7(V45)}}
	base[0]=base[0];
	return Cnil;
}
