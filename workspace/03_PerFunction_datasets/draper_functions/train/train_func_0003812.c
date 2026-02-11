LI28(V267)

register object V267;
{	 VMB28 VMS28 VMV28
	goto TTL;
TTL:;
	{register object V268;
	V268= (VFUN_NARGS=0,(*(LnkLI222))(small_fixnum(0)));
	V269= Ct;
	STSET(object,(V268),0, ((object)VV[96]));
	(void)(((object)VV[96]));
	{object V270;
	if(type_of(CMPcar((V267)))==t_cons){
	goto T743;}
	V270= Cnil;
	goto T742;
	goto T743;
T743:;
	if((CMPcaar((V267)))==(((object)VV[99]))){
	goto T745;}
	V270= Cnil;
	goto T742;
	goto T745;
T745:;
	{object V271;
	V271= CMPcdr(CMPcar((V267)));
	if((V271)==Cnil){
	V270= Cnil;
	goto T742;}
	if((CMPcddr((V271)))==Cnil){
	goto T748;}
	V270= Cnil;
	goto T742;
	goto T748;
T748:;
	V270= list(4,((object)VV[4]),(V268),((object)VV[100]),(*(LnkLI234))((V271),(V268)));}
	goto T742;
T742:;
	if(((V270))==Cnil){
	goto T751;}
	{object V272 = (V270);
	VMR28(V272)}
	goto T751;
T751:;
	V267= (*(LnkLI234))((V267),(V268));
	{object V273 = list(4,((object)VV[4]),(V268),((object)VV[101]),(V267));
	VMR28(V273)}}}
	return Cnil;
}
