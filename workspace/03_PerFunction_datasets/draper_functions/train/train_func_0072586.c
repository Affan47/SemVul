assign_temp_tablespaces(const char *newval, bool doit, GucSource source)
{
	char	   *rawname;
	List	   *namelist;


	rawname = pstrdup(newval);


	if (!SplitIdentifierString(rawname, ',', &namelist))
	{

		pfree(rawname);
		list_free(namelist);
		return NULL;
	}


	if (IsTransactionState())
	{


		Oid		   *tblSpcs;
		int			numSpcs;
		ListCell   *l;

		tblSpcs = (Oid *) MemoryContextAlloc(TopTransactionContext,
										list_length(namelist) * sizeof(Oid));
		numSpcs = 0;
		foreach(l, namelist)
		{
			char	   *curname = (char *) lfirst(l);
			Oid			curoid;
			AclResult	aclresult;


			if (curname[0] == '\0')
			{
				tblSpcs[numSpcs++] = InvalidOid;
				continue;
			}


			curoid = get_tablespace_oid(curname, source < PGC_S_INTERACTIVE);
			if (curoid == InvalidOid)
				continue;


			if (curoid == MyDatabaseTableSpace)
			{
				tblSpcs[numSpcs++] = InvalidOid;
				continue;
			}


			aclresult = pg_tablespace_aclcheck(curoid, GetUserId(),
											   ACL_CREATE);
			if (aclresult != ACLCHECK_OK)
			{
				if (source >= PGC_S_INTERACTIVE)
					aclcheck_error(aclresult, ACL_KIND_TABLESPACE, curname);
				continue;
			}

			tblSpcs[numSpcs++] = curoid;
		}


		if (doit)
			SetTempTablespaces(tblSpcs, numSpcs);
		else
			pfree(tblSpcs);
	}

	pfree(rawname);
	list_free(namelist);

	return newval;
}
