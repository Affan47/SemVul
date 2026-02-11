ps_sym_def(char *name, struct elt_s *e)
{
	struct ps_sym_s *ps;

	if (n_sym > 0) {
		ps = &ps_sym[n_sym];
		for (;;) {
			ps--;
			if (ps == ps_sym)
				break;
			if (strcmp(ps->n, name) == 0) {
				elt_free(ps->e);
				ps->e = e;
				return;
			}
		}
	}
	if (n_sym >= NSYMS) {
		fprintf(stderr, "svg: Too many PS symbols\n");
		ps_error = 1;
		return;
	}
	ps_sym[n_sym].n = strdup(name);
	ps_sym[n_sym].e = e;
	ps_sym[n_sym].exec = 0;
	n_sym++;
}
