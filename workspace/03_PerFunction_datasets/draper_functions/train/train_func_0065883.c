CopyVar(SplitVar *s, int makedup)
{
	SplitVar   *v = (SplitVar *) palloc(sizeof(SplitVar));

	v->next = NULL;
	if (s)
	{
		int			i;

		v->lenstem = s->lenstem;
		v->stem = (char **) palloc(sizeof(char *) * v->lenstem);
		v->nstem = s->nstem;
		for (i = 0; i < s->nstem; i++)
			v->stem[i] = (makedup) ? pstrdup(s->stem[i]) : s->stem[i];
	}
	else
	{
		v->lenstem = 16;
		v->stem = (char **) palloc(sizeof(char *) * v->lenstem);
		v->nstem = 0;
	}
	return v;
}
