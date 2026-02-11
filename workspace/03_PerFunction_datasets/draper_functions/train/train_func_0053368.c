free_symbol_table(SymbolTable * symtab)
{
    int i;
    Symbol *sym, *next;

    for (i = 0; i < SYM_MAX_HASH; ++i) {
	sym = symtab->bucket[i];
	while (sym != NULL) {
	    next = sym->next;
	    if (sym->name != 0)
		free(sym->name);
	    if (sym->value != 0)
		free(sym->value);
	    free(sym);
	    sym = next;
	}
    }
    free(symtab);
}
