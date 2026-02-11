print(FILE *fp, struct scope *s)
{
	struct declaration *d;

	for (d = s->declaration_first; d; d = d->next) {
		print_declaration(fp, 0, d);
	}
}
