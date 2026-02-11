assign_locus(struct grecs_locus_point *ploc,
	     char *name, char *line, size_t *pxlines)
{
	char *p;

	if (name) {
		if (pxlines && (!ploc->file || strcmp(name, ploc->file)))
			*pxlines = 0;
		ploc->file = grecs_install_text(name);
	}
	ploc->line = strtoul(line, &p, 10) - (pxlines ? *pxlines : 0);
	ploc->col = 0;
	return *p != 0;
}
