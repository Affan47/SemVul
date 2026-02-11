sym_enter(name, type)
char   *name;
int     type;
{
    struct symbol *s;
    int     where;

    if ((s = (struct symbol *) malloc(sizeof(*s))) == 0
	|| (s->name = malloc(strlen(name) + 1)) == 0)
	fatal("out of memory");
    (void) strcpy(s->name, name);
    s->type = type;

    where = hash(name, SYM_TABSIZE);
    s->next = sym_tab[where];
    sym_tab[where] = s;
}
