extractbindings(Tree *tree0) {
	Chain me;
	Tree *volatile tree = tree0;
	Binding *volatile bindings = NULL;

	gcdisable();

	if (tree->kind == nList && tree->u[1].p == NULL)
		tree = tree->u[0].p;

	me.closure = mkclosure(NULL, NULL);
	me.next = chain;
	chain = &me;

	ExceptionHandler

		while (tree->kind == nClosure) {
			bindings = extract(tree->u[0].p, bindings);
			tree = tree->u[1].p;
			if (tree->kind == nList && tree->u[1].p == NULL)
				tree = tree->u[0].p;
		}

	CatchException (e)

		chain = chain->next;
		throw(e);

	EndExceptionHandler

	chain = chain->next;

	Ref(Closure *, result, me.closure);
	result->tree = tree;
	result->binding = bindings;
	gcenable();
	RefReturn(result);
}
