genExpr( Junction *j )
#else
genExpr( j )
Junction *j;
#endif
{
	int max_k;


	{
		int limit;
		if ( j->ftree!=NULL ) limit = LL_k;
		else limit = CLL_k;
		max_k = genExprSets(j->fset, limit);
	}


	if ( j->ftree != NULL )
	{
		_gen(" && !("); genExprTree(j->ftree, 1); _gen(")");
	}

	if ( ParseWithPredicates && j->predicate!=NULL )
	{
		Predicate *p = j->predicate;
		warn_about_using_gk_option();
		_gen("&&");
		j->predicate=genPredTreeMain(p, (Node *)j);
	}

	return max_k;
}
