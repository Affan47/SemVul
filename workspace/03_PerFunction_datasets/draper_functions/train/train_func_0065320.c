LI7__SET_DIFFERENCE_REV__listlib(object V77,object V76,object first,...)
{
	va_list ap;
	int narg = VFUN_NARGS; VMB7 VMS7 VMV7
	{object V78;
	register object V79;
	register object V80;
	register object V81;
	register object V82;
	va_start(ap,first);
	V78= V77;
	V79= V76;
	narg= narg - 2;
	{
	parse_key_new_new(narg,Vcs +2,(struct key *)(void *)&LI7key,first,ap);
	V80=(Vcs[2]);
	V81=(Vcs[3]);
	V82=(Vcs[4]);
	{register object V83;
	V83= Cnil;
	{register object V84;
	V84= (V78);
	goto T151;
T151:;
	if(((V84))!=Cnil){
	goto T152;}
	{object V85 = (V83);
	VMR7(V85)}
	goto T152;
T152:;
	if(!(type_of((V84))==t_cons)){
	goto T157;}
	goto T156;
	goto T157;
T157:;
	(void)((VFUN_NARGS=1,(*(LnkLI23))(((object)VV[8]),small_fixnum(0))));
	goto T156;
T156:;
	base[0]=((object)VV[24])->s.s_gfdef;
	base[1]= CMPcar((V84));
	base[2]= (V79);
	base[3]= ((object)VV[9]);
	base[4]= Ct;
	{object V86;
	V86= (*(LnkLI25))((V82),(V80),(V81));
	 vs_top=base+5;
	 while(V86!=Cnil)
	 {vs_push((V86)->c.c_car);V86=(V86)->c.c_cdr;}
	vs_base=base+1;}
	(void) (*Lnk24)();
	vs_top=sup;
	if((vs_base[0])!=Cnil){
	goto T159;}
	V83= make_cons(CMPcar((V84)),(V83));
	goto T159;
T159:;
	V84= CMPcdr((V84));
	goto T151;}}
	va_end(ap);
	base[0]=base[0];
	return Cnil;}
	}}
