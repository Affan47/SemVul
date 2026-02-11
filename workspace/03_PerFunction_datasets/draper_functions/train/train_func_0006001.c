pushstring(char *s, struct alias *ap)
{
	struct strpush *sp;
	int len;

	len = strlen(s);
	INT_OFF;
	if (g_parsefile->strpush) {
		sp = ckzalloc(sizeof(*sp));
		sp->prev = g_parsefile->strpush;
	} else {
		sp = &(g_parsefile->basestrpush);
	}
	g_parsefile->strpush = sp;
	sp->prev_string = g_parsefile->next_to_pgetc;
	sp->prev_left_in_line = g_parsefile->left_in_line;
#if ENABLE_ASH_ALIAS
	sp->ap = ap;
	if (ap) {
		ap->flag |= ALIASINUSE;
		sp->string = s;
	}
#endif
	g_parsefile->next_to_pgetc = s;
	g_parsefile->left_in_line = len;
	INT_ON;
}
