rexpr(expr, s)
char *expr, *s;
#endif
{
	NodePtr p,q;
	Graph nfa;
	int result;

	fprintf(stderr, "rexpr(%s,%s);\n", expr,s);
	freelist = NULL;
	_c = expr;
	next();
	if ( regExpr(&nfa) == -1 ) return -1;
	accept = nfa.right;
	result = match(nfa.left, s);

	p = q = freelist;
	while ( p!=NULL ) { q = p->track; free(p); p = q; }
	return result;
}
