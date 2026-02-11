parse(char *line, size_t linelen, struct headline *hl, char *pbuf)
{
	char *cp;
	char *sp;
	char *word;

	hl->l_from = NULL;
	hl->l_tty = NULL;
	hl->l_date = NULL;
	cp = line;
	sp = pbuf;
	word = ac_alloc(linelen + 1);


	cp = nextword(cp, word);
	cp = nextword(cp, word);
	if (*word)
		hl->l_from = copyin(word, &sp);
	if (cp != NULL && cp[0] == 't' && cp[1] == 't' && cp[2] == 'y') {
		cp = nextword(cp, word);
		hl->l_tty = copyin(word, &sp);
	}
	if (cp != NULL)
		hl->l_date = copyin(cp, &sp);
	else
		hl->l_date = catgets(catd, CATSET, 213, "<Unknown date>");
	ac_free(word);
}
