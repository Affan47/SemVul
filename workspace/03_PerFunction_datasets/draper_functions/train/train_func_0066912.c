postquel_sub_params(SQLFunctionCachePtr fcache,
					FunctionCallInfo fcinfo)
{
	int			nargs = fcinfo->nargs;

	if (nargs > 0)
	{
		ParamListInfo paramLI;
		int			i;

		if (fcache->paramLI == NULL)
		{

			paramLI = (ParamListInfo) palloc(sizeof(ParamListInfoData) +
									   (nargs - 1) *sizeof(ParamExternData));
			paramLI->numParams = nargs;
			fcache->paramLI = paramLI;
		}
		else
		{
			paramLI = fcache->paramLI;
			Assert(paramLI->numParams == nargs);
		}

		for (i = 0; i < nargs; i++)
		{
			ParamExternData *prm = &paramLI->params[i];

			prm->value = fcinfo->arg[i];
			prm->isnull = fcinfo->argnull[i];
			prm->pflags = 0;
			prm->ptype = fcache->argtypes[i];
		}
	}
	else
		fcache->paramLI = NULL;
}
