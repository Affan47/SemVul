emit_header ()
{
	GList *l;

	output ("#include <glib.h>\n");
	output ("\n");

	output ("#ifndef MBTREE_TYPE\n#error MBTREE_TYPE undefined\n#endif\n");
	output ("#ifndef MBTREE_OP\n#define MBTREE_OP(t) ((t)->op)\n#endif\n");
	output ("#ifndef MBTREE_LEFT\n#define MBTREE_LEFT(t) ((t)->left)\n#endif\n");
	output ("#ifndef MBTREE_RIGHT\n#define MBTREE_RIGHT(t) ((t)->right)\n#endif\n");
	output ("#ifndef MBTREE_STATE\n#define MBTREE_STATE(t) ((t)->state)\n#endif\n");
	output ("#ifndef MBREG_TYPE\n#define MBREG_TYPE gint32\n#endif\n");
	output ("#ifndef MBCGEN_TYPE\n#define MBCGEN_TYPE int\n#endif\n");
	output ("#ifndef MBALLOC_STATE\n#define MBALLOC_STATE g_new (MBState, 1)\n#endif\n");
	output ("#ifndef MBCOST_DATA\n#define MBCOST_DATA gpointer\n#endif\n");
	output ("\n");
	output ("#define MBMAXCOST 32768\n");

	output ("\n");
	output ("#define MBCOND(x) if (!(x)) return MBMAXCOST;\n");

	output ("\n");

	for (l = term_list; l; l = l->next) {
		Term *t = (Term *)l->data;
		if (t->number == -1)
			t->number = next_term_num ();
	}
	term_list = g_list_sort (term_list, (GCompareFunc)term_compare_func);

	for (l = term_list; l; l = l->next) {
		Term *t = (Term *)l->data;
		if (t->number == -1)
			t->number = next_term_num ();

		if (predefined_terms)
			output ("#define MB_TERM_%s\t %s\n", t->name, t->name);
		else
			output ("#define MB_TERM_%s\t %d\n", t->name, t->number);

	}
	output ("\n");

}
