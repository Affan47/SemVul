content_base(struct rfc2045 *p, struct rfc822t *t)
{
char	*s;
int	i;

	for (i=0; i<t->ntokens; i++)
		if (t->tokens[i].token == '"')
			t->tokens[i].token=0;

	s=paste_tokens(t, 2, t->ntokens-2);
	set_string(&p->content_base, s);
}
