LI14__REPLACE_CONSTANT__cmpeval(V152)

object V152;
{	 VMB14 VMS14 VMV14
	goto TTL;
TTL:;
	{register object V153;
	register object V154;
	V153= Cnil;
	V154= Cnil;
	{register object V155;
	V155= (V152);
	goto T435;
T435:;
	if(((V155))!=Cnil){
	goto T436;}
	{object V156 = (V153);
	VMR14(V156)}
	goto T436;
T436:;
	base[0]= CMPcar((V155));
	vs_top=(vs_base=base+0)+1;
	Lconstantp();
	vs_top=sup;
	if((vs_base[0])==Cnil){
	goto T440;}
	base[0]= CMPcar((V155));
	vs_top=(vs_base=base+0)+1;
	Leval();
	vs_top=sup;
	V154= vs_base[0];
	if(type_of((V154))==t_fixnum||
type_of((V154))==t_bignum||
type_of((V154))==t_ratio||
type_of((V154))==t_shortfloat||
type_of((V154))==t_longfloat||
type_of((V154))==t_complex){
	goto T441;}
	if(!(type_of((V154))==t_character)){
	goto T440;}
	goto T441;
T441:;
	V153= Ct;
	{register object V157;
	register object V158;
	V157= (V155);
	V158= (V154);
	((V157))->c.c_car = (V158);}
	goto T440;
T440:;
	V155= CMPcdr((V155));
	goto T435;}}
	base[0]=base[0];
	return Cnil;
}
