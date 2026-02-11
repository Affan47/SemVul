FindConversionByName(List *name)
{
	char	   *schemaname;
	char	   *conversion_name;
	Oid			namespaceId;
	Oid			conoid;
	ListCell   *l;


	DeconstructQualifiedName(name, &schemaname, &conversion_name);

	if (schemaname)
	{

		namespaceId = LookupExplicitNamespace(schemaname);
		return FindConversion(conversion_name, namespaceId);
	}
	else
	{

		recomputeNamespacePath();

		foreach(l, activeSearchPath)
		{
			namespaceId = lfirst_oid(l);

			if (namespaceId == myTempNamespace)
				continue;

			conoid = FindConversion(conversion_name, namespaceId);
			if (OidIsValid(conoid))
				return conoid;
		}
	}


	return InvalidOid;
}
