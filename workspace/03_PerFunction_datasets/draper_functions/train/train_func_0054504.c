PerlIO_destruct(pTHX)
{
    dVAR;
    PerlIOl **table = &PL_perlio;
    PerlIOl *f;
#ifdef USE_ITHREADS
    PerlIO_debug("Destruct %p\n",(void*)aTHX);
#endif
    while ((f = *table)) {
	int i;
	table = (PerlIOl **) (f++);
	for (i = 1; i < PERLIO_TABLE_SIZE; i++) {
	    PerlIO *x = &(f->next);
	    const PerlIOl *l;
	    while ((l = *x)) {
		if (l->tab && l->tab->kind & PERLIO_K_DESTRUCT) {
		    PerlIO_debug("Destruct popping %s\n", l->tab->name);
		    PerlIO_flush(x);
		    PerlIO_pop(aTHX_ x);
		}
		else {
		    x = PerlIONext(x);
		}
	    }
	    f++;
	}
    }
}
