LI8(V30)

object V30;
{	 VMB8 VMS8 VMV8
	goto TTL;
TTL:;
	{register object V31;
	(((object)VV[22])->s.s_dbind)= immnum_plus((((object)VV[22])->s.s_dbind),small_fixnum(1));
	V31= (VFUN_NARGS=4,(*(LnkLI92))(((object)VV[19]),((object)VV[20]),((object)VV[21]),(((object)VV[22])->s.s_dbind)));
	{object V32;
	if(((((object)VV[24])->s.s_dbind))!=Cnil){
	goto T80;}
	V33= Cnil;
	goto T78;
	goto T80;
T80:;
	V33= make_cons(small_fixnum(0),small_fixnum(0));
	goto T78;
T78:;
	V32= list(5,((object)VV[23]),V33,(((object)VV[25])->s.s_dbind),(V31),(V30));
	(((object)VV[26])->s.s_dbind)= make_cons((V32),(((object)VV[26])->s.s_dbind));}
	(((object)VV[27])->s.s_dbind)= make_cons(V31,(((object)VV[27])->s.s_dbind));
	{object V35;
	V35= STREF(object,(V31),24);
	(((object)VV[12])->s.s_dbind)= make_cons((V35),(((object)VV[12])->s.s_dbind));}
	V36= list(3,((object)VV[29]),STREF(object,(V31),24),(((object)VV[24])->s.s_dbind));
	{object V37 = (VFUN_NARGS=1,(*(LnkLI93))(V36,small_fixnum(0)));
	VMR8(V37)}}
	return Cnil;
}
