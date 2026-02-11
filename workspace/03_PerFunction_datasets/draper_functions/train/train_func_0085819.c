dumplocs()
{
    register struct symstruct *symptr;
    int i;

#ifdef ASM_USES_CALLEE_REGS
    if (framep && optimise && !callersaves) {
       regfuse |= callee1mask;
       outnstr("! Assuming #asm uses all callee saves registers");
    }
#endif

    for (i = 0; i < HASHTABSIZE; ++i)
	for (symptr = hashtab[i]; symptr != NULL; symptr = symptr->next)
	    if (symptr->storage == LOCAL)
		set(symptr->name.namea, symptr->offset.offi - sp);
}
