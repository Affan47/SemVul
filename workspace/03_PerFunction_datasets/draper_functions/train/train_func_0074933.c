OpfamilynameGetOpfid(Oid amid, const char *opfname)
{
	Oid			opfid;
	ListCell   *l;

	recomputeNamespacePath();

	foreach(l, activeSearchPath)
	{
		Oid			namespaceId = lfirst_oid(l);

		if (namespaceId == myTempNamespace)
			continue;

		opfid = GetSysCacheOid(OPFAMILYAMNAMENSP,
							   ObjectIdGetDatum(amid),
							   PointerGetDatum(opfname),
							   ObjectIdGetDatum(namespaceId),
							   0);
		if (OidIsValid(opfid))
			return opfid;
	}


	return InvalidOid;
}
