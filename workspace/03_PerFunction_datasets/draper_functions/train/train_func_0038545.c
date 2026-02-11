expandarg(union node *arg, struct arglist *arglist, int flag)
{
	struct strlist *sp;
	char *p;

	argbackq = arg->narg.backquote;
	STARTSTACKSTR(expdest);
	ifsfirst.next = NULL;
	ifslastp = NULL;
	argstr(arg->narg.text, flag,
			 arglist ? arglist->list : NULL);
	p = _STPUTC('\0', expdest);
	expdest = p - 1;
	if (arglist == NULL) {
		return;
	}
	p = grabstackstr(p);
	exparg.lastp = &exparg.list;


	if (flag & EXP_FULL) {
		ifsbreakup(p, &exparg);
		*exparg.lastp = NULL;
		exparg.lastp = &exparg.list;
		expandmeta(exparg.list );
	} else {
		if (flag & EXP_REDIR)
			rmescapes(p, 0);
		sp = stzalloc(sizeof(*sp));
		sp->text = p;
		*exparg.lastp = sp;
		exparg.lastp = &sp->next;
	}
	if (ifsfirst.next)
		ifsfree();
	*exparg.lastp = NULL;
	if (exparg.list) {
		*arglist->lastp = exparg.list;
		arglist->lastp = exparg.lastp;
	}
}
