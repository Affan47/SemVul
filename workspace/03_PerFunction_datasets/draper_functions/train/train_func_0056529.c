LI14(V157)

register object V157;
{	 VMB14 VMS14 VMV14
	goto TTL;
TTL:;
	{register object V158;
	V158= (VFUN_NARGS=0,(*(LnkLI222))(small_fixnum(0)));
	if(((V157))==Cnil){
	goto T502;}
	if(!((CMPcdr((V157)))==Cnil)){
	goto T501;}
	goto T502;
T502:;
	V159 = CMPmake_fixnum((long)(length((V157))));
	(void)((*(LnkLI223))(((object)VV[49]),small_fixnum(2),V159));
	goto T501;
T501:;
	if(!((CMPcddr((V157)))==Cnil)){
	goto T507;}
	{object V160 = list(4,((object)VV[47]),(V158),((object)VV[50]),(*(LnkLI234))((V157),(V158)));
	VMR14(V160)}
	goto T507;
T507:;
	if(!((CMPcaddr((V157)))==(((object)VV[51])))){
	goto T510;}
	if(!(((long)length((V157)))==((long)4))){
	goto T510;}
	{register object x= CMPcadddr((V157)),V161= ((object)VV[52]);
	while(V161!=Cnil)
	if(equal(x,V161->c.c_car)){
	goto T515;
	}else V161=V161->c.c_cdr;
	goto T510;}
	goto T515;
T515:;
	V162= CMPcadr(CMPcadddr((V157)));
	V163= list(2,CMPcar((V157)),CMPcadr((V157)));
	{object V164 = list(4,((object)VV[47]),(V158),V162,(*(LnkLI234))(V163,(V158)));
	VMR14(V164)}
	goto T510;
T510:;
	{object V165 = list(4,((object)VV[4]),(V158),((object)VV[49]),(*(LnkLI234))((V157),(V158)));
	VMR14(V165)}}
	return Cnil;
}
