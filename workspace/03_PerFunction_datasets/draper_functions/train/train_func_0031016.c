AlterOpClassOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Oid			namespaceOid;
	AclResult	aclresult;
	Form_pg_opclass opcForm;

	Assert(tup->t_tableOid == OperatorClassRelationId);
	Assert(RelationGetRelid(rel) == OperatorClassRelationId);

	opcForm = (Form_pg_opclass) GETSTRUCT(tup);

	namespaceOid = opcForm->opcnamespace;


	if (opcForm->opcowner != newOwnerId)
	{

		if (!superuser())
		{

			if (!pg_opclass_ownercheck(HeapTupleGetOid(tup), GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_OPCLASS,
							   NameStr(opcForm->opcname));


			check_is_member_of_role(GetUserId(), newOwnerId);


			aclresult = pg_namespace_aclcheck(namespaceOid, newOwnerId,
											  ACL_CREATE);
			if (aclresult != ACLCHECK_OK)
				aclcheck_error(aclresult, ACL_KIND_NAMESPACE,
							   get_namespace_name(namespaceOid));
		}


		opcForm->opcowner = newOwnerId;

		simple_heap_update(rel, &tup->t_self, tup);

		CatalogUpdateIndexes(rel, tup);


		changeDependencyOnOwner(OperatorClassRelationId, HeapTupleGetOid(tup),
								newOwnerId);
	}
}
