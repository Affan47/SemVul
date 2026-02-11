LI6__SET_DIFFERENCE__listlib(object V66,object V65,object first,...)
{
	va_list ap;
	int narg = VFUN_NARGS; VMB6 VMS6 VMV6
	{object V67;
	register object V68;
	register object V69;
	register object V70;
	register object V71;
	va_start(ap,first);
	V67= V66;
	V68= V65;
	narg= narg - 2;
	{
	parse_key_new_new(narg,Vcs +2,(struct key *)(void *)&LI6key,first,ap);
	V69=(Vcs[2]);
	V70=(Vcs[3]);
	V71=(Vcs[4]);
	{register object V72;
	V72= Cnil;
	{register object V73;
	V73= (V67);
	goto T131;
T131:;
	if(((V73))!=Cnil){
	goto T132;}
	{object V74 = (V72);
	VMR6(V74)}
	goto T132;
T132:;
	if(!(type_of((V73))==t_cons)){
	goto T137;}
	goto T136;
	goto T137;
T137:;
	(void)((VFUN_NARGS=1,(*(LnkLI23))(((object)VV[7]),small_fixnum(0))));
	goto T136;
T136:;
	base[0]=((object)VV[24])->s.s_gfdef;
	base[1]= CMPcar((V73));
	base[2]= (V68);
	{object V75;
	V75= (*(LnkLI25))((V71),(V69),(V70));
	 vs_top=base+3;
	 while(V75!=Cnil)
	 {vs_push((V75)->c.c_car);V75=(V75)->c.c_cdr;}
	vs_base=base+1;}
	(void) (*Lnk24)();
	vs_top=sup;
	if((vs_base[0])!=Cnil){
	goto T139;}
	V72= make_cons(CMPcar((V73)),(V72));
	goto T139;
T139:;
	V73= CMPcdr((V73));
	goto T131;}}
	va_end(ap);
	base[0]=base[0];
	return Cnil;}
	}}
