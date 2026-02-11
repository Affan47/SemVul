svg_close(void)
{
	struct elt_s *e, *e2;

	setg(0);
	fputs("</svg>\n", fout);
	e = stack;
	if (e != 0) {
		stack = 0;
		fprintf(stderr, "svg close: stack not empty ");
		elt_lst_dump(e);
		fprintf(stderr, "\n");
		do {
			e2 = e->next;
			elt_free(e);
			e = e2;
		} while (e != 0);
	}
}
