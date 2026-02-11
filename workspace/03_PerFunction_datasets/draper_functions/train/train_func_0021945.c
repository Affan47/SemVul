CheckMyDatabase(const char *name, bool am_superuser)
{
	HeapTuple	tup;
	Form_pg_database dbform;
	char	   *collate;
	char	   *ctype;


	tup = SearchSysCache(DATABASEOID,
						 ObjectIdGetDatum(MyDatabaseId),
						 0, 0, 0);
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for database %u", MyDatabaseId);
	dbform = (Form_pg_database) GETSTRUCT(tup);


	if (strcmp(name, NameStr(dbform->datname)) != 0)
		ereport(FATAL,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" has disappeared from pg_database",
						name),
				 errdetail("Database OID %u now seems to belong to \"%s\".",
						   MyDatabaseId, NameStr(dbform->datname))));


	if (IsUnderPostmaster && !IsAutoVacuumWorkerProcess())
	{


		if (!dbform->datallowconn)
			ereport(FATAL,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
			 errmsg("database \"%s\" is not currently accepting connections",
					name)));


		if (!am_superuser &&
			pg_database_aclcheck(MyDatabaseId, GetUserId(),
								 ACL_CONNECT) != ACLCHECK_OK)
			ereport(FATAL,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied for database \"%s\"", name),
					 errdetail("User does not have CONNECT privilege.")));


		if (dbform->datconnlimit >= 0 &&
			!am_superuser &&
			CountDBBackends(MyDatabaseId) > dbform->datconnlimit)
			ereport(FATAL,
					(errcode(ERRCODE_TOO_MANY_CONNECTIONS),
					 errmsg("too many connections for database \"%s\"",
							name)));
	}


	SetDatabaseEncoding(dbform->encoding);

	SetConfigOption("server_encoding", GetDatabaseEncodingName(),
					PGC_INTERNAL, PGC_S_OVERRIDE);

	SetConfigOption("client_encoding", GetDatabaseEncodingName(),
					PGC_BACKEND, PGC_S_DEFAULT);


	collate = NameStr(dbform->datcollate);
	ctype = NameStr(dbform->datctype);

	if (pg_perm_setlocale(LC_COLLATE, collate) == NULL)
		ereport(FATAL,
			(errmsg("database locale is incompatible with operating system"),
			 errdetail("The database was initialized with LC_COLLATE \"%s\", "
					   " which is not recognized by setlocale().", collate),
			 errhint("Recreate the database with another locale or install the missing locale.")));

	if (pg_perm_setlocale(LC_CTYPE, ctype) == NULL)
		ereport(FATAL,
			(errmsg("database locale is incompatible with operating system"),
			 errdetail("The database was initialized with LC_CTYPE \"%s\", "
					   " which is not recognized by setlocale().", ctype),
			 errhint("Recreate the database with another locale or install the missing locale.")));


	SetConfigOption("lc_collate", collate, PGC_INTERNAL, PGC_S_OVERRIDE);
	SetConfigOption("lc_ctype", ctype, PGC_INTERNAL, PGC_S_OVERRIDE);


#ifdef ENABLE_NLS
	pg_bind_textdomain_codeset(textdomain(NULL));
#endif


	if (IsUnderPostmaster)
	{
		Datum		datum;
		bool		isnull;

		datum = SysCacheGetAttr(DATABASEOID, tup, Anum_pg_database_datconfig,
								&isnull);
		if (!isnull)
		{
			ArrayType  *a = DatumGetArrayTypeP(datum);


			ProcessGUCArray(a, PGC_SUSET, PGC_S_DATABASE, GUC_ACTION_SET);
		}
	}

	ReleaseSysCache(tup);
}
