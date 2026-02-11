gda_sql_statement_string_to_type (const gchar *type)
{
	g_return_val_if_fail (type, GDA_SQL_STATEMENT_NONE);

	switch (*type) {
	case 'B':
		return GDA_SQL_STATEMENT_BEGIN;
	case 'C':
		if ((type[1] == 'O') && (type[2] == 'M') && (type[2] == 'P'))
			return GDA_SQL_STATEMENT_COMPOUND;
		else
			return GDA_SQL_STATEMENT_COMMIT;
	case 'D':
		if (!strcmp (type, "DELETE"))
			return GDA_SQL_STATEMENT_DELETE;
		else
			return GDA_SQL_STATEMENT_DELETE_SAVEPOINT;
	case 'I':
		return GDA_SQL_STATEMENT_INSERT;
	case 'R':
		if (!strcmp (type, "ROLLBACK"))
			return GDA_SQL_STATEMENT_ROLLBACK;
		else
			return GDA_SQL_STATEMENT_ROLLBACK_SAVEPOINT;
	case 'S':
		if (type[1] == 'E')
			return GDA_SQL_STATEMENT_SELECT;
		else
			return GDA_SQL_STATEMENT_SAVEPOINT;
	case 'U':
		if (type[1] == 'N')
			return GDA_SQL_STATEMENT_UNKNOWN;
		else
			return GDA_SQL_STATEMENT_UPDATE;
	default:
		TO_IMPLEMENT;
		return GDA_SQL_STATEMENT_NONE;
	}
}
