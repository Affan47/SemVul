AlterConversionOwner_internal(Relation rel, Oid conversionOid, Oid newOwnerId)
{
	Form_pg_conversion convForm;
	HeapTuple	tup;

	Assert(RelationGetRelid(rel) == ConversionRelationId);

	tup = SearchSysCacheCopy(CONVOID,
							 ObjectIdGetDatum(conversionOid),
							 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for conversion %u", conversionOid);

	convForm = (Form_pg_conversion) GETSTRUCT(tup);


	if (convForm->conowner != newOwnerId)
	{
		AclResult	aclresult;


		if (!superuser())
		{

			if (!pg_conversion_ownercheck(HeapTupleGetOid(tup), GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_CONVERSION,
							   NameStr(convForm->conname));


			check_is_member_of_role(GetUserId(), newOwnerId);


			aclresult = pg_namespace_aclcheck(convForm->connamespace,
											  newOwnerId,
											  ACL_CREATE);
			if (aclresult != ACLCHECK_OK)
				aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
							   get_namespace_name(convForm->connamespace));
		}


		convForm->conowner = newOwnerId;

		simple_heap_update(rel, &tup->t_self, tup);

		CatalogUpdateIndexes(rel, tup);


		changeDependencyOnOwner(ConversionRelationId, conversionOid,
								newOwnerId);
	}

	heap_freetuple(tup);
}
