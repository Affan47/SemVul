LI39__C1NTH_CONDITION__cmpfun(V388)

register object V388;
{	 VMB39 VMS39 VMV39
	goto TTL;
TTL:;
	if(((((V388))==Cnil?Ct:Cnil))==Cnil){
	goto T987;}
	{object V389 = Cnil;
	VMR39(V389)}
	goto T987;
T987:;
	if((((CMPcdr((V388)))==Cnil?Ct:Cnil))==Cnil){
	goto T989;}
	{object V390 = Cnil;
	VMR39(V390)}
	goto T989;
T989:;
	if((CMPcddr((V388)))==Cnil){
	goto T991;}
	{object V391 = Cnil;
	VMR39(V391)}
	goto T991;
T991:;
	{object V392= CMPcar((V388));
	if(type_of(V392)==t_fixnum||
type_of(V392)==t_bignum||
type_of(V392)==t_ratio||
type_of(V392)==t_shortfloat||
type_of(V392)==t_longfloat||
type_of(V392)==t_complex){
	goto T993;}}
	{object V393 = Cnil;
	VMR39(V393)}
	goto T993;
T993:;
	base[0]= small_fixnum(0);
	base[1]= CMPcar((V388));
	base[2]= small_fixnum(7);
	vs_top=(vs_base=base+0)+3;
	Lmonotonically_nondecreasing();
	vs_top=sup;
	{object V394 = vs_base[0];
	VMR39(V394)}
	base[0]=base[0];
	return Cnil;
}
