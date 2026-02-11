ExecAlterObjectSchemaStmt(AlterObjectSchemaStmt *stmt)
{
	switch (stmt->objectType)
	{
		case OBJECT_AGGREGATE:
			AlterFunctionNamespace(stmt->object, stmt->objarg, true,
								   stmt->newschema);
			break;

		case OBJECT_FUNCTION:
			AlterFunctionNamespace(stmt->object, stmt->objarg, false,
								   stmt->newschema);
			break;

		case OBJECT_SEQUENCE:
		case OBJECT_TABLE:
		case OBJECT_VIEW:
			CheckRelationOwnership(stmt->relation, true);
			AlterTableNamespace(stmt->relation, stmt->newschema,
								stmt->objectType);
			break;

		case OBJECT_TYPE:
		case OBJECT_DOMAIN:
			AlterTypeNamespace(stmt->object, stmt->newschema);
			break;

		default:
			elog(ERROR, "unrecognized AlterObjectSchemaStmt type: %d",
				 (int) stmt->objectType);
	}
}
