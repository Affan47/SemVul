print1(Symtab *s)
{
	Word *w;

	Bprint(&bout, "\t%s=", s->name);
	for (w = s->u.ptr; w; w = w->next)
		Bprint(&bout, "'%s'", w->s);
	Bprint(&bout, "\n");
}
