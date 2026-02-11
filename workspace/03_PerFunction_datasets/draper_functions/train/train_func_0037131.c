ProcessOpt(const char *opt, PLOptionTable *tab, int *p_myargc, char ***p_argv,
	   int *p_argc)
{
    int need_arg, res;
    char *myoptarg = NULL;


    need_arg = PL_OPT_ARG | PL_OPT_INT | PL_OPT_FLOAT | PL_OPT_STRING;

    if (tab->mode & need_arg) {
	if (GetOptarg(&myoptarg, p_myargc, p_argv, p_argc))
	    return 1;
    }


    switch (tab->mode & 0xFF00) {

    case PL_OPT_FUNC:


	if (tab->handler == NULL) {
	    fprintf(stderr,
		    "ProcessOpt: no handler specified for option %s\n",
		    tab->opt);
	    return 1;
	}

        if (mode_nodelete && myoptarg) {


	    char *copy =
	      (char *) malloc((size_t)(1+strlen(myoptarg))*sizeof(char));
	    if (copy == NULL) {
	        plabort("ProcessOpt: out of memory");
		return 1;
	    }
	    strcpy(copy, myoptarg);
	    res = ((*tab->handler) (opt, copy, tab->client_data));
	    free((void *) copy);
	    return res;
	}
	else {
	  return ((*tab->handler) (opt, myoptarg, tab->client_data));
	}

    case PL_OPT_BOOL:


	if (tab->var == NULL) {
	    fprintf(stderr,
		    "ProcessOpt: no variable specified for option %s\n",
		    tab->opt);
	    return 1;
	}
	*(int *)tab->var = 1;
	break;

    case PL_OPT_INT:


	if (tab->var == NULL) {
	    fprintf(stderr,
		    "ProcessOpt: no variable specified for option %s\n",
		    tab->opt);
	    return 1;
	}
	*(int *)tab->var = atoi(myoptarg);
	break;

    case PL_OPT_FLOAT:


	if (tab->var == NULL) {
	    fprintf(stderr,
		    "ProcessOpt: no variable specified for option %s\n",
		    tab->opt);
	    return 1;
	}
	*(PLFLT *)tab->var = atof(myoptarg);
	break;

    case PL_OPT_STRING:


	*(char **)tab->var = (char *)myoptarg;
	break;

    default:


	fprintf(stderr,
		"ProcessOpt: invalid processing mode for option %s\n",
		tab->opt);
	return 1;
    }
    return 0;
}
