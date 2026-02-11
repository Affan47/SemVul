GenRulePrototypes( FILE *f, int tabs )
#else
GenRulePrototypes( f, tabs )
FILE *f;
int tabs;
#endif
{
	AST *p;
	SymEntry *s;

	for (p=rules; p!=NULL; p=p->right)
	{
		int i;
		s = (SymEntry *) hash_get(symbols, p->text);
		require(s!=NULL, "GenRulePrototypes: sym tab broken");

		for (i=1; i<=tabs; i++) fprintf(f, "\t");
		GenRulePrototype(f, p, s, 1);
	}
}
