PerlIOBase_dup(pTHX_ PerlIO *f, PerlIO *o, CLONE_PARAMS *param, int flags)
{
    PerlIO * const nexto = PerlIONext(o);
    if (PerlIOValid(nexto)) {
	const PerlIO_funcs * const tab = PerlIOBase(nexto)->tab;
	if (tab && tab->Dup)
	    f = (*tab->Dup)(aTHX_ f, nexto, param, flags);
	else
	    f = PerlIOBase_dup(aTHX_ f, nexto, param, flags);
    }
    if (f) {
	PerlIO_funcs * const self = PerlIOBase(o)->tab;
	SV *arg = NULL;
	char buf[8];
	PerlIO_debug("PerlIOBase_dup %s f=%p o=%p param=%p\n",
		     self ? self->name : "(Null)",
		     (void*)f, (void*)o, (void*)param);
	if (self && self->Getarg)
	    arg = (*self->Getarg)(aTHX_ o, param, flags);
	f = PerlIO_push(aTHX_ f, self, PerlIO_modestr(o,buf), arg);
	if (f && PerlIOBase(o)->flags & PERLIO_F_UTF8)
	    PerlIOBase(f)->flags |= PERLIO_F_UTF8;
	SvREFCNT_dec(arg);
    }
    return f;
}
