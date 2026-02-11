get_object_address_unqualified(ObjectType objtype, List *qualname)
{
	const char *name;
	ObjectAddress address;


	if (list_length(qualname) != 1)
	{
		const char *msg;

		switch (objtype)
		{
			case OBJECT_DATABASE:
				msg = gettext_noop("database name cannot be qualified");
				break;
			case OBJECT_EXTENSION:
				msg = gettext_noop("extension name cannot be qualified");
				break;
			case OBJECT_TABLESPACE:
				msg = gettext_noop("tablespace name cannot be qualified");
				break;
			case OBJECT_ROLE:
				msg = gettext_noop("role name cannot be qualified");
				break;
			case OBJECT_SCHEMA:
				msg = gettext_noop("schema name cannot be qualified");
				break;
			case OBJECT_LANGUAGE:
				msg = gettext_noop("language name cannot be qualified");
				break;
			case OBJECT_FDW:
				msg = gettext_noop("foreign-data wrapper name cannot be qualified");
				break;
			case OBJECT_FOREIGN_SERVER:
				msg = gettext_noop("server name cannot be qualified");
				break;
			default:
				elog(ERROR, "unrecognized objtype: %d", (int) objtype);
				msg = NULL;
		}
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("%s", _(msg))));
	}


	name = strVal(linitial(qualname));


	switch (objtype)
	{
		case OBJECT_DATABASE:
			address.classId = DatabaseRelationId;
			address.objectId = get_database_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_EXTENSION:
			address.classId = ExtensionRelationId;
			address.objectId = get_extension_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_TABLESPACE:
			address.classId = TableSpaceRelationId;
			address.objectId = get_tablespace_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_ROLE:
			address.classId = AuthIdRelationId;
			address.objectId = get_role_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_SCHEMA:
			address.classId = NamespaceRelationId;
			address.objectId = get_namespace_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_LANGUAGE:
			address.classId = LanguageRelationId;
			address.objectId = get_language_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_FDW:
			address.classId = ForeignDataWrapperRelationId;
			address.objectId = get_foreign_data_wrapper_oid(name, false);
			address.objectSubId = 0;
			break;
		case OBJECT_FOREIGN_SERVER:
			address.classId = ForeignServerRelationId;
			address.objectId = get_foreign_server_oid(name, false);
			address.objectSubId = 0;
			break;
		default:
			elog(ERROR, "unrecognized objtype: %d", (int) objtype);

			address.classId = InvalidOid;
			address.objectId = InvalidOid;
			address.objectSubId = 0;
	}

	return address;
}
