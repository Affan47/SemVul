has_any_column_privilege_id_name(PG_FUNCTION_ARGS)
{
	Oid			roleid = PG_GETARG_OID(0);
	text	   *tablename = PG_GETARG_TEXT_P(1);
	text	   *priv_type_text = PG_GETARG_TEXT_P(2);
	Oid			tableoid;
	AclMode		mode;
	AclResult	aclresult;

	tableoid = convert_table_name(tablename);
	mode = convert_column_priv_string(priv_type_text);


	aclresult = pg_class_aclcheck(tableoid, roleid, mode);
	if (aclresult != ACLCHECK_OK)
		aclresult = pg_attribute_aclcheck_all(tableoid, roleid, mode,
											  ACLMASK_ANY);

	PG_RETURN_BOOL(aclresult == ACLCHECK_OK);
}
