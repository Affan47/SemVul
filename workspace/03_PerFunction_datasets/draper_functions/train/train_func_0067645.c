LI7(object first,...)
{
	va_list ap;
	int narg = VFUN_NARGS; VMB7 VMS7 VMV7
	{object V25;
	va_start(ap,first);
	narg = narg - 0;
	if (narg <= 0) goto T50;
	else {
	V25= first;}
	--narg; goto T51;
	goto T50;
T50:;
	V25= (((object)VV[9])->s.s_dbind);
	goto T51;
T51:;
	if(((V25))!=Cnil){
	goto T54;}
	princ_str("Cnil",((object)VV[4]));
	{object V26 = Cnil;
	VMR7(V26)}
	goto T54;
T54:;
	{object V27 = (*(LnkLI12))((V25));
	VMR7(V27)}
	va_end(ap);
	return Cnil;}
	}
