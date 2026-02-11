LI54__LOOP_EMIT_FINAL_VALUE__loop(V336)

object V336;
{	 VMB46 VMS46 VMV46
	goto TTL;
TTL:;
	{object V337;
	V337= (*(LnkLI360))((V336));
	(((object)VV[113])->s.s_dbind)= make_cons((V337),(((object)VV[113])->s.s_dbind));}
	if(((((object)VV[114])->s.s_dbind))==Cnil){
	goto T755;}
	if(((((object)VV[119])->s.s_dbind))==Cnil){
	goto T759;}
	(void)((VFUN_NARGS=3,(*(LnkLI348))(((object)VV[90]),((object)VV[131]),(((object)VV[114])->s.s_dbind),small_fixnum(0))));
	goto T755;
	goto T759;
T759:;
	(void)((VFUN_NARGS=2,(*(LnkLI340))(((object)VV[132]),(((object)VV[114])->s.s_dbind))));
	goto T755;
T755:;
	(((object)VV[114])->s.s_dbind)= CMPcar((((object)VV[88])->s.s_dbind));
	{object V338 = (((object)VV[114])->s.s_dbind);
	VMR46(V338)}
	return Cnil;
}
