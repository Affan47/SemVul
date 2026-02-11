caltdissect(struct vars * v,
			struct subre * t,
			chr *begin,
			chr *end)
{
	struct dfa *d;
	int			er;


	while (t != NULL)
	{
		assert(t->op == '|');
		assert(t->left != NULL && t->left->cnfa.nstates > 0);

		MDEBUG(("calt n%d\n", t->id));

		d = getsubdfa(v, t->left);
		NOERR();
		if (longest(v, d, begin, end, (int *) NULL) == end)
		{
			MDEBUG(("calt matched\n"));
			er = cdissect(v, t->left, begin, end);
			if (er != REG_NOMATCH)
				return er;
		}

		t = t->right;
	}

	return REG_NOMATCH;
}
