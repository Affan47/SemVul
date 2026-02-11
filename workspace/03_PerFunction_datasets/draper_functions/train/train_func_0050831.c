parseheredoc(void)
{
	struct heredoc *here;
	union node *n;

	here = heredoclist;
	heredoclist = NULL;

	while (here) {
		setprompt_if(needprompt, 2);
		readtoken1(pgetc(), here->here->type == NHERE ? SQSYNTAX : DQSYNTAX,
				here->eofmark, here->striptabs);
		n = stzalloc(sizeof(struct narg));
		n->narg.type = NARG;

		n->narg.text = wordtext;
		n->narg.backquote = backquotelist;
		here->here->nhere.doc = n;
		here = here->next;
	}
}
