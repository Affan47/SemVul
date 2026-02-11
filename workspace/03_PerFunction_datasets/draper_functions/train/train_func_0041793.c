CacheInvalidateCatalog(Oid catalogId)
{
	Oid			databaseId;

	if (IsSharedRelation(catalogId))
		databaseId = InvalidOid;
	else
		databaseId = MyDatabaseId;

	RegisterCatalogInvalidation(databaseId, catalogId);
}
