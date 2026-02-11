PerlIO_cleantable(pTHX_ PerlIOl **tablep)
{
    PerlIOl * const table = *tablep;
    if (table) {
	int i;
	PerlIO_cleantable(aTHX_(PerlIOl **) & (table[0]));
	for (i = PERLIO_TABLE_SIZE - 1; i > 0; i--) {
	    PerlIOl * const f = table + i;
	    if (f->next) {
		PerlIO_close(&(f->next));
	    }
	}
	Safefree(table);
	*tablep = NULL;
    }
}
