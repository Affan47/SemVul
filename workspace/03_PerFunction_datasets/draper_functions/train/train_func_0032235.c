CheckAttributeType(const char *attname, Oid atttypid)
{
	char		att_typtype = get_typtype(atttypid);


	if (atttypid == UNKNOWNOID)
		ereport(WARNING,
				(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
				 errmsg("column \"%s\" has type \"unknown\"", attname),
				 errdetail("Proceeding with relation creation anyway.")));
	else if (att_typtype == 'p')
	{

		if (atttypid != ANYARRAYOID || IsUnderPostmaster)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
					 errmsg("column \"%s\" has pseudo-type %s",
							attname, format_type_be(atttypid))));
	}
}
