transformWindowFuncCall(ParseState *pstate, WindowFunc *wfunc,
						WindowDef *windef)
{


	if (pstate->p_hasWindowFuncs &&
		checkExprHasWindowFuncs((Node *) wfunc->args))
		ereport(ERROR,
				(errcode(ERRCODE_WINDOWING_ERROR),
				 errmsg("window function calls cannot be nested"),
				 parser_errposition(pstate,
								  locate_windowfunc((Node *) wfunc->args))));


	if (windef->name)
	{
		Index		winref = 0;
		ListCell   *lc;

		Assert(windef->refname == NULL &&
			   windef->partitionClause == NIL &&
			   windef->orderClause == NIL &&
			   windef->frameOptions == FRAMEOPTION_DEFAULTS);

		foreach(lc, pstate->p_windowdefs)
		{
			WindowDef  *refwin = (WindowDef *) lfirst(lc);

			winref++;
			if (refwin->name && strcmp(refwin->name, windef->name) == 0)
			{
				wfunc->winref = winref;
				break;
			}
		}
		if (lc == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("window \"%s\" does not exist", windef->name),
					 parser_errposition(pstate, windef->location)));
	}
	else
	{
		Index		winref = 0;
		ListCell   *lc;

		foreach(lc, pstate->p_windowdefs)
		{
			WindowDef  *refwin = (WindowDef *) lfirst(lc);

			winref++;
			if (refwin->refname && windef->refname &&
				strcmp(refwin->refname, windef->refname) == 0)
				  ;
			else if (!refwin->refname && !windef->refname)
				  ;
			else
				continue;
			if (equal(refwin->partitionClause, windef->partitionClause) &&
				equal(refwin->orderClause, windef->orderClause) &&
				refwin->frameOptions == windef->frameOptions)
			{

				wfunc->winref = winref;
				break;
			}
		}
		if (lc == NULL)
		{
			pstate->p_windowdefs = lappend(pstate->p_windowdefs, windef);
			wfunc->winref = list_length(pstate->p_windowdefs);
		}
	}

	pstate->p_hasWindowFuncs = true;
}
