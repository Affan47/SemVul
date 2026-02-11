evalfun(struct funcnode *func, int argc, char **argv, int flags)
{
	volatile struct shparam saveparam;
	struct localvar *volatile savelocalvars;
	struct jmploc *volatile savehandler;
	struct jmploc jmploc;
	int e;

	saveparam = shellparam;
	savelocalvars = localvars;
	e = setjmp(jmploc.loc);
	if (e) {
		goto funcdone;
	}
	INT_OFF;
	savehandler = exception_handler;
	exception_handler = &jmploc;
	localvars = NULL;
	shellparam.malloced = 0;
	func->count++;
	funcnest++;
	INT_ON;
	shellparam.nparam = argc - 1;
	shellparam.p = argv + 1;
#if ENABLE_ASH_GETOPTS
	shellparam.optind = 1;
	shellparam.optoff = -1;
#endif
	evaltree(&func->n, flags & EV_TESTED);
 funcdone:
	INT_OFF;
	funcnest--;
	freefunc(func);
	poplocalvars();
	localvars = savelocalvars;
	freeparam(&shellparam);
	shellparam = saveparam;
	exception_handler = savehandler;
	INT_ON;
	evalskip &= ~SKIPFUNC;
	return e;
}
