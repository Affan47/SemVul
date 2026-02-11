LI14__COMPILER_CC__cmpmain(V142,V143)

object V142;object V143;
{	 VMB12 VMS12 VMV12
	goto TTL;
TTL:;
	base[0]= Cnil;
	{object V145;
	V145= (VFUN_NARGS=2,(*(LnkLI260))((V142),(V143)));
	base[1]= (V145);}
	base[2]= (((object)VV[134])->s.s_dbind);
	if(immnum_eq((((object)VV[138])->s.s_dbind),small_fixnum(2))){
	goto T816;}
	if(!(immnum_eq((((object)VV[138])->s.s_dbind),small_fixnum(3)))){
	goto T817;}
	goto T816;
T816:;
	base[3]= Ct;
	goto T815;
	goto T817;
T817:;
	base[3]= Cnil;
	goto T815;
T815:;
	base[5]= (V142);
	vs_top=(vs_base=base+5)+1;
	Lnamestring();
	vs_top=sup;
	base[4]= vs_base[0];
	base[6]= (V143);
	vs_top=(vs_base=base+6)+1;
	Lnamestring();
	vs_top=sup;
	base[5]= vs_base[0];
	vs_top=(vs_base=base+0)+6;
	Lformat();
	vs_top=sup;
	V144= vs_base[0];
	{object V146 = (*(LnkLI253))(V144);
	VMR12(V146)}
	base[0]=base[0];
	return Cnil;
}
