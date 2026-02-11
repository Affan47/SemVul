bg_mknode(holenode *p) {
	if(DEBUG) fprintf(stderr, "BUG: parser::bg_mknode(holenode): ");

	if(p == NULL) return new nil();

	if(DEBUG) cerr << p->to_string() << endl;

	return new hole(p->n);
}
