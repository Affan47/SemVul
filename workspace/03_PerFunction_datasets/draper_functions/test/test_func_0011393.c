AssignTypeArrayOid(void)
{
	Oid			type_array_oid;


	if (IsBinaryUpgrade && OidIsValid(binary_upgrade_next_array_pg_type_oid))
	{
		type_array_oid = binary_upgrade_next_array_pg_type_oid;
		binary_upgrade_next_array_pg_type_oid = InvalidOid;
	}
	else
	{
		Relation	pg_type = heap_open(TypeRelationId, AccessShareLock);

		type_array_oid = GetNewOid(pg_type);
		heap_close(pg_type, AccessShareLock);
	}

	return type_array_oid;
}
