LI78(V497)

object V497;
{	 VMB67 VMS67 VMV67
	goto TTL;
TTL:;
	if(((V497))==Cnil){
	goto T1129;}
	vs_base=vs_top;
	(void) (*Lnk367)();
	vs_top=sup;
	goto T1129;
T1129:;
	V498= (*(LnkLI383))();
	vs_base=vs_top;
	(void) (*Lnk366)();
	vs_top=sup;
	V499= vs_base[0];
	V500= list(3,((object)VV[11]),V498,V499);
	V501= list(3,((object)VV[8]),V500,(*(LnkLI360))((((object)VV[116])->s.s_dbind)));
	(void)((*(LnkLI369))(V501));
	{object V502 = (*(LnkLI377))(Cnil);
	VMR67(V502)}
	base[0]=base[0];
	return Cnil;
}
