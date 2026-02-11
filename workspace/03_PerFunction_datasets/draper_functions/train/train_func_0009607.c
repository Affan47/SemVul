printRegisteredCounterInfo (FILE *tf)
{
    StgEntCounter *p;

    if ( ticky_entry_ctrs != NULL ) {
      fprintf(tf,"\n**************************************************\n\n");
    }
    fprintf(tf, "%11s%11s %6s%6s    %-11s%-30s\n",
	    "Entries", "Allocs", "Arity", "Stack", "Kinds", "Function");
    fprintf(tf, "--------------------------------------------------------------------------------\n");


    for (p = ticky_entry_ctrs; p != NULL; p = p->link) {
	fprintf(tf, "%11" FMT_Int "%11" FMT_Int " %6lu%6lu    %-11s%-30s",
		p->entry_count,
		p->allocs,
		(unsigned long)p->arity,
		(unsigned long)p->stk_args,
		p->arg_kinds,
		p->str);

	fprintf(tf, "\n");

    }
}
