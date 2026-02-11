OpernameGetCandidates(List *names, char oprkind)
{
	FuncCandidateList resultList = NULL;
	char	   *resultSpace = NULL;
	int			nextResult = 0;
	char	   *schemaname;
	char	   *opername;
	Oid			namespaceId;
	CatCList   *catlist;
	int			i;


	DeconstructQualifiedName(names, &schemaname, &opername);

	if (schemaname)
	{

		namespaceId = LookupExplicitNamespace(schemaname);
	}
	else
	{

		namespaceId = InvalidOid;
		recomputeNamespacePath();
	}


	catlist = SearchSysCacheList1(OPERNAMENSP, CStringGetDatum(opername));


#define SPACE_PER_OP MAXALIGN(sizeof(struct _FuncCandidateList) + sizeof(Oid))

	if (catlist->n_members > 0)
		resultSpace = palloc(catlist->n_members * SPACE_PER_OP);

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	opertup = &catlist->members[i]->tuple;
		Form_pg_operator operform = (Form_pg_operator) GETSTRUCT(opertup);
		int			pathpos = 0;
		FuncCandidateList newResult;


		if (oprkind && operform->oprkind != oprkind)
			continue;

		if (OidIsValid(namespaceId))
		{

			if (operform->oprnamespace != namespaceId)
				continue;

		}
		else
		{


			ListCell   *nsp;

			foreach(nsp, activeSearchPath)
			{
				if (operform->oprnamespace == lfirst_oid(nsp) &&
					operform->oprnamespace != myTempNamespace)
					break;
				pathpos++;
			}
			if (nsp == NULL)
				continue;


			if (resultList)
			{
				FuncCandidateList prevResult;

				if (catlist->ordered)
				{
					if (operform->oprleft == resultList->args[0] &&
						operform->oprright == resultList->args[1])
						prevResult = resultList;
					else
						prevResult = NULL;
				}
				else
				{
					for (prevResult = resultList;
						 prevResult;
						 prevResult = prevResult->next)
					{
						if (operform->oprleft == prevResult->args[0] &&
							operform->oprright == prevResult->args[1])
							break;
					}
				}
				if (prevResult)
				{

					Assert(pathpos != prevResult->pathpos);
					if (pathpos > prevResult->pathpos)
						continue;

					prevResult->pathpos = pathpos;
					prevResult->oid = HeapTupleGetOid(opertup);
					continue;
				}
			}
		}


		newResult = (FuncCandidateList) (resultSpace + nextResult);
		nextResult += SPACE_PER_OP;

		newResult->pathpos = pathpos;
		newResult->oid = HeapTupleGetOid(opertup);
		newResult->nargs = 2;
		newResult->nvargs = 0;
		newResult->ndargs = 0;
		newResult->argnumbers = NULL;
		newResult->args[0] = operform->oprleft;
		newResult->args[1] = operform->oprright;
		newResult->next = resultList;
		resultList = newResult;
	}

	ReleaseSysCacheList(catlist);

	return resultList;
}
