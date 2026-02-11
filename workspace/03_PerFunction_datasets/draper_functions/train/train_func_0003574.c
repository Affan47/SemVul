parse(char *pr1, char *pr2) {
	int result;
	assert(error == NULL);

	inityy();
	emptyherequeue();

	if (ISEOF(input))
		throw(mklist(mkstr("eof"), NULL));

#if READLINE
	prompt = (pr1 == NULL) ? "" : pr1;
#else
	if (pr1 != NULL)
		eprint("%s", pr1);
#endif
	prompt2 = pr2;

	gcreserve(300 * sizeof (Tree));
	gcdisable();
	result = yyparse();
	gcenable();

	if (result || error != NULL) {
		char *e;
		assert(error != NULL);
		e = error;
		error = NULL;
		fail("$&parse", "%s", e);
	}
#if LISPTREES
	if (input->runflags & run_lisptrees)
		eprint("%B\n", parsetree);
#endif
	return parsetree;
}
