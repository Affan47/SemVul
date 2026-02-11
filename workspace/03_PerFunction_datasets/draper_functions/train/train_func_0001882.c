sql_exec_error_callback(void *arg)
{
	FmgrInfo   *flinfo = (FmgrInfo *) arg;
	SQLFunctionCachePtr fcache = (SQLFunctionCachePtr) flinfo->fn_extra;
	int			syntaxerrposition;


	if (fcache == NULL || fcache->fname == NULL)
		return;


	syntaxerrposition = geterrposition();
	if (syntaxerrposition > 0 && fcache->src != NULL)
	{
		errposition(0);
		internalerrposition(syntaxerrposition);
		internalerrquery(fcache->src);
	}


	if (fcache->func_state)
	{
		execution_state *es;
		int			query_num;

		es = fcache->func_state;
		query_num = 1;
		while (es)
		{
			if (es->qd)
			{
				errcontext("SQL function \"%s\" statement %d",
						   fcache->fname, query_num);
				break;
			}
			es = es->next;
			query_num++;
		}
		if (es == NULL)
		{


			errcontext("SQL function \"%s\"", fcache->fname);
		}
	}
	else
	{


		errcontext("SQL function \"%s\" during startup", fcache->fname);
	}
}
