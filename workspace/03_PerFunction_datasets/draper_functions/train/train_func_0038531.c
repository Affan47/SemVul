dumptree(Paragraph *pp, Stack *sp, FILE *f)
{
    int count;
    Line *p;
    int d;
    static char *Begin[] = { 0, "P", "center" };

    while ( pp ) {
	if ( !pp->next )
	    changepfx(sp, '`');
	printpfx(sp, f);

	d = fprintf(f, "[%s", Pptype(pp->typ));
	if ( pp->ident )
	    d += fprintf(f, " %s", pp->ident);
	if ( pp->align )
	    d += fprintf(f, ", <%s>", Begin[pp->align]);

	for (count=0, p=pp->text; p; ++count, (p = p->next) )
	    ;

	if ( count )
	    d += fprintf(f, ", %d line%s", count, (count==1)?"":"s");

	d += fprintf(f, "]");

	if ( pp->down ) {
	    pushpfx(d, pp->down->next ? '+' : '-', sp);
	    dumptree(pp->down, sp, f);
	    poppfx(sp);
	}
	else fputc('\n', f);
	pp = pp->next;
    }
}
