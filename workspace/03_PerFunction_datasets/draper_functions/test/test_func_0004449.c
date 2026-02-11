ldregargs()
{
    register struct symstruct *symptr;
    store_pt targreg;
    struct symstruct temptarg;

    for (symptr = &locsyms[0]; symptr < locptr && symptr->level == ARGLEVEL;
	 symptr = (struct symstruct *)
		  align(&symptr->name.namea[strlen(symptr->name.namea) + 1]))
    {
	if ((store_t) (targreg = symptr->storage) & allregs)
	{


	    temptarg = *symptr;
	    if (arg1inreg && symptr == &locsyms[0])
	    {
		temptarg.storage = ARGREG;
		temptarg.offset.offi = 0;
	    }
	    else
	    {
		temptarg.storage = LOCAL;
		temptarg.indcount = 1;
	    }
	    load(&temptarg, targreg);
	    symptr->offset.offi = 0;
	}
    }
    regarg = FALSE;
}
