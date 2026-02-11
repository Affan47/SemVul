prog_init(void)
	{
	LHASH_OF(FUNCTION) *ret;
	FUNCTION *f;
	size_t i;


	for(i=0,f=functions ; f->name != NULL ; ++f,++i)
	    ;
	qsort(functions,i,sizeof *functions,SortFnByName);

	if ((ret=lh_FUNCTION_new()) == NULL)
		return(NULL);

	for (f=functions; f->name != NULL; f++)
		(void)lh_FUNCTION_insert(ret,f);
	return(ret);
	}
