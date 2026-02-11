PerlIOScalar_set_ptrcnt(pTHX_ PerlIO * f, STDCHAR * ptr, SSize_t cnt)
{
    PerlIOScalar *s = PerlIOSelf(f, PerlIOScalar);
    STRLEN len;
    PERL_UNUSED_ARG(ptr);
    SvGETMAGIC(s->var);
    if (isGV_with_GP(s->var)) (void)SvPV(s->var,len);
    else len = SvCUR(s->var);
    s->posn = len - cnt;
}
