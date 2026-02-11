processtypesizes(void)
{
    int i;

    for(i=0;i<listlength(typdefs);i++) {
	Symbol* tsym = (Symbol*)listget(typdefs,i);
	tsym->touched = 0;
    }
    for(i=0;i<listlength(typdefs);i++) {
	Symbol* tsym = (Symbol*)listget(typdefs,i);
	computesize(tsym);
    }
}
