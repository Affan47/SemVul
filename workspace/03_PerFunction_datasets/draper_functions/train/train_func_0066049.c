apply (fun, vfunc, arg)
  int  (*fun)(), (*vfunc)();
  char  *arg;
{
    register char *flag;
    register bptr b;
    register int  i, j, found;
    char *p;

#ifdef TCL_IRSIM

    int start, argc;
    char **argv;

    if (targc == applyStart + 1)
    {
	Tcl_SplitList(irsiminterp, targv[applyStart], &argc, (CONST char ***)&argv);
	if (argc > 1)
	    start = 0;
	else
	{
	    Tcl_Free((char *)argv);
	    argv = targv;
	    argc = targc;
	    start = applyStart;
	}
    }
    else
    {
	argv = targv;
	argc = targc;
	start = applyStart;
    }

    for (i = start; i < argc; i++)
    {
	p = argv[i];

#else

    for (i = applyStart; i < targc; i++)
    {
	p = targv[i];

#endif

	if (arg == plus_minus)
	{
	    if (*p == '-')
	    {
		flag = p;
		p++;
	    }
	    else
		flag = plus_minus;
	}
	else
	    flag = arg;

	found = 0;
	if (wildCard[i])
	{
	    for (b = blist; b != NULL; b = b->next)
		if (str_match(p, b->name ))
		{
		    if (vfunc != NULL)
			(*vfunc)(b, flag);
		    else
			for (j = 0; j < b->nbits; j++)
			    (*fun)(b->nodes[j], flag);
		    found = 1;
		}
	    found += match_net(p, fun, flag);
	}
	else
	{
	    nptr n = find(p);

	    if (n != NULL)
		found += (*fun)(n, flag);
	    else
	    {
		for (b = blist; b != NULL; b = b->next)
		    if (str_eql(p, b->name) == 0)
		    {
			if (vfunc != NULL)
			    (*vfunc)(b, flag);
			else
			    for (j = 0; j < b->nbits; j++)
				(*fun)(b->nodes[j], flag);
			found = 1;
			break;
		    }
	    }
	}
	if (found == 0)
	    rsimerror(filename, lineno, "%s: No such node or vector\n", p);
    }

#ifdef TCL_IRSIM
    if (argv != targv) Tcl_Free((char *)argv);
#endif

}
