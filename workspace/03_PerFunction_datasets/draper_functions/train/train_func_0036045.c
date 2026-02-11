FcSubstDestroy (FcSubst *s)
{
    FcSubst *n;

    while (s)
    {
	n = s->next;
	if (s->rule)
	    FcRuleDestroy (s->rule);
	free (s);
	s = n;
    }
}
