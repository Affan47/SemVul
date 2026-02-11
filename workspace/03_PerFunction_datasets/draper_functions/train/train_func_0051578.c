XS_Fcntl_S_ISREG(pTHX_ CV* cv)
{
    dVAR;
    dXSARGS;
    dXSI32;


    SV *mode;

    PERL_UNUSED_VAR(cv);
    SP -= items;

    if (items > 0)
	mode = ST(0);
    else {
	mode = &PL_sv_undef;
	EXTEND(SP, 1);
    }
    PUSHs(((SvUV(mode) & S_IFMT) == (UV)ix) ? &PL_sv_yes : &PL_sv_no);
    PUTBACK;
}
