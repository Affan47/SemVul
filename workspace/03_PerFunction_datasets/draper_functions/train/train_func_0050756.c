LI37(object V306,object first,...)
{
	va_list ap;
	int narg = VFUN_NARGS; VMB37 VMS37 VMV37
	{register object V307;
	object V308;
	object V309;
	object V310;
	object V311;
	va_start(ap,first);
	V307= V306;
	narg = narg - 1;
	if (narg <= 0) goto T782;
	else {
	V308= first;}
	if (--narg <= 0) goto T783;
	else {
	V309= va_arg(ap,object);}
	if (--narg <= 0) goto T784;
	else {
	V310= va_arg(ap,object);}
	if (--narg <= 0) goto T785;
	else {
	V311= va_arg(ap,object);}
	--narg; goto T786;
	goto T782;
T782:;
	V308= Cnil;
	goto T783;
T783:;
	V309= Cnil;
	goto T784;
T784:;
	V310= Cnil;
	goto T785;
T785:;
	V311= Cnil;
	goto T786;
T786:;
	{object V312;
	V312= (((V307))==Cnil?Ct:Cnil);
	if(((V312))==Cnil){
	goto T793;}
	{object V313 = (V312);
	VMR37(V313)}
	goto T793;
T793:;
	if(!(type_of((V307))==t_symbol)){
	goto T796;}
	{object V314 = (VFUN_NARGS=7,(*(LnkLI268))((V307),(V308),(V310),(V309),Cnil,Ct,(V311)));
	VMR37(V314)}
	goto T796;
T796:;
	if(!(type_of((V307))==t_cons||((V307))==Cnil)){
	goto T799;}
	(void)((VFUN_NARGS=1,(*(LnkLI269))(CMPcar((V307)),small_fixnum(0))));
	{object V315 = (VFUN_NARGS=1,(*(LnkLI269))(CMPcdr((V307)),small_fixnum(0)));
	VMR37(V315)}
	goto T799;
T799:;
	{object V316 = Cnil;
	VMR37(V316)}}
	va_end(ap);
	return Cnil;}
	}
