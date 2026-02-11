AlterFunctionNamespace(List *name, List *argtypes, bool isagg,
					   const char *newschema)
{
	Oid			procOid;
	Oid			oldNspOid;
	Oid			nspOid;
	HeapTuple	tup;
	Relation	procRel;
	Form_pg_proc proc;

	procRel = heap_open(ProcedureRelationId, RowExclusiveLock);


	if (isagg)
		procOid = LookupAggNameTypeNames(name, argtypes, false);
	else
		procOid = LookupFuncNameTypeNames(name, argtypes, false);


	if (!pg_proc_ownercheck(procOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_PROC,
					   NameListToString(name));

	tup = SearchSysCacheCopy1(PROCOID, ObjectIdGetDatum(procOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for function %u", procOid);
	proc = (Form_pg_proc) GETSTRUCT(tup);

	oldNspOid = proc->pronamespace;


	nspOid = LookupCreationNamespace(newschema);


	CheckSetNamespace(oldNspOid, nspOid, ProcedureRelationId, procOid);


	if (SearchSysCacheExists3(PROCNAMEARGSNSP,
							  CStringGetDatum(NameStr(proc->proname)),
							  PointerGetDatum(&proc->proargtypes),
							  ObjectIdGetDatum(nspOid)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_FUNCTION),
				 errmsg("function \"%s\" already exists in schema \"%s\"",
						NameStr(proc->proname),
						newschema)));


	proc->pronamespace = nspOid;

	simple_heap_update(procRel, &tup->t_self, tup);
	CatalogUpdateIndexes(procRel, tup);


	if (changeDependencyFor(ProcedureRelationId, procOid,
							NamespaceRelationId, oldNspOid, nspOid) != 1)
		elog(ERROR, "failed to change schema dependency for function \"%s\"",
			 NameListToString(name));

	heap_freetuple(tup);

	heap_close(procRel, RowExclusiveLock);
}
