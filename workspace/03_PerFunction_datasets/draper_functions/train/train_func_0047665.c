setxysym(char *op, int use)
{
	struct elt_s *e;
	struct ps_sym_s *sym;
	float x, y;

	y = pop_free_val();
	x = pop_free_val();
	sym = ps_sym_lookup("x");
	if (sym->e->type != VAL) {
		e = elt_new();
		e->type = VAL;
		ps_sym_def("x", e);
	}
	sym->e->u.v = x;
	sym = ps_sym_lookup("y");
	if (sym->e->type != VAL) {
		e = elt_new();
		e->type = VAL;
		ps_sym_def("y", e);
	}
	sym->e->u.v = y;
	def_use(use);
	fprintf(fout, "<use x=\"%.2f\" y=\"%.2f\" xlink:href=\"#%s\"/>\n",
		xoffs + x, yoffs - y, op);
}
