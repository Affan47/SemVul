evalfun(struct funcnode *func, int argc, char **argv, int flags)
{
	volatile struct shparam saveparam;
	struct jmploc *volatile savehandler;
	struct jmploc jmploc;
	int e;
	int savefuncline;

	saveparam = shellparam;
	savefuncline = funcline;
	savehandler = handler;
	if ((e = setjmp(jmploc.loc))) {
		goto funcdone;
	}
	INTOFF;
	handler = &jmploc;
	shellparam.malloc = 0;
	func->count++;
	funcline = func->n.ndefun.linno;
	INTON;
	shellparam.nparam = argc - 1;
	shellparam.p = argv + 1;
	shellparam.optind = 1;
	shellparam.optoff = -1;
	pushlocalvars();
	evaltree(func->n.ndefun.body, flags & EV_TESTED);
	poplocalvars(0);
funcdone:
	INTOFF;
	funcline = savefuncline;
	freefunc(func);
	freeparam(&shellparam);
	shellparam = saveparam;
	handler = savehandler;
	INTON;
	evalskip &= ~SKIPFUNC;
	return e;
}
