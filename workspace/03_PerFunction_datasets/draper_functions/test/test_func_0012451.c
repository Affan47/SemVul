binding(Format *f, char *keyword, Tree *tree) {
	Tree *np;
	char *sep = "";
	fmtprint(f, "%s(", keyword);
	for (np = tree->u[0].p; np != NULL; np = np->u[1].p) {
		Tree *binding;
		assert(np->kind == nList);
		binding = np->u[0].p;
		assert(binding != NULL);
		assert(binding->kind == nAssign);
		fmtprint(f, "%s%#T=%T", sep, binding->u[0].p, binding->u[1].p);
		sep = ";";
	}
	fmtprint(f, ")");
}
