LI44__ARGS_CAUSE_SIDE_EFFECT__cmpinline(V411)

object V411;
{	 VMB44 VMS44 VMV44
	goto TTL;
TTL:;
	{register object V412;
	V412= Cnil;
	{register object V413;
	register object V414;
	V413= (V411);
	V414= CMPcar((V413));
	goto T964;
T964:;
	if(!(((V413))==Cnil)){
	goto T965;}
	{object V415 = Cnil;
	VMR44(V415)}
	goto T965;
T965:;
	{object V416= CMPcar((V414));
	if((V416!= ((object)VV[38]))
	&& (V416!= ((object)VV[24]))
	&& (V416!= ((object)VV[129])))goto T970;
	goto T969;
	goto T970;
T970:;
	if((V416!= ((object)VV[115])))goto T971;
	{register object V417;
	V417= CMPcaddr((V414));
	if(((*(LnkLI116))((V417)))==Cnil){
	goto T973;}
	V412= (*(LnkLI117))((V417),CMPcadddr((V414)),STREF(object,CMPcadr((V414)),0));
	if(((V412))==Cnil){
	goto T973;}
	(void)((*(LnkLI139))((V412)));
	if(((immnum_bitp(small_fixnum(1),CMPcaddr((V412)))?Ct:Cnil))==Cnil){
	goto T969;}
	goto T973;
T973:;
	{object V418 = Ct;
	VMR44(V418)}}
	goto T971;
T971:;
	{object V419 = Ct;
	VMR44(V419)}}
	goto T969;
T969:;
	V413= CMPcdr((V413));
	V414= CMPcar((V413));
	goto T964;}}
	return Cnil;
}
