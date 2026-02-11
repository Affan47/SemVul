FindDefaultConversionProc(int4 for_encoding, int4 to_encoding)
{
	Oid			proc;
	ListCell   *l;

	recomputeNamespacePath();

	foreach(l, activeSearchPath)
	{
		Oid			namespaceId = lfirst_oid(l);

		if (namespaceId == myTempNamespace)
			continue;

		proc = FindDefaultConversion(namespaceId, for_encoding, to_encoding);
		if (OidIsValid(proc))
			return proc;
	}


	return InvalidOid;
}
