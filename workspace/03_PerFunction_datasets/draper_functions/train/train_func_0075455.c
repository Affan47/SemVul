ExecAlterExtensionStmt(AlterExtensionStmt *stmt)
{
	DefElem    *d_new_version = NULL;
	char	   *versionName;
	char	   *oldVersionName;
	ExtensionControlFile *control;
	Oid			extensionOid;
	Relation	extRel;
	ScanKeyData key[1];
	SysScanDesc extScan;
	HeapTuple	extTup;
	List	   *updateVersions;
	Datum		datum;
	bool		isnull;
	ListCell   *lc;


	if (creating_extension)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("nested ALTER EXTENSION is not supported")));


	extRel = heap_open(ExtensionRelationId, AccessShareLock);

	ScanKeyInit(&key[0],
				Anum_pg_extension_extname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(stmt->extname));

	extScan = systable_beginscan(extRel, ExtensionNameIndexId, true,
								 SnapshotNow, 1, key);

	extTup = systable_getnext(extScan);

	if (!HeapTupleIsValid(extTup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("extension \"%s\" does not exist",
						stmt->extname)));

	extensionOid = HeapTupleGetOid(extTup);


	datum = heap_getattr(extTup, Anum_pg_extension_extversion,
						 RelationGetDescr(extRel), &isnull);
	if (isnull)
		elog(ERROR, "extversion is null");
	oldVersionName = text_to_cstring(DatumGetTextPP(datum));

	systable_endscan(extScan);

	heap_close(extRel, AccessShareLock);


	if (!pg_extension_ownercheck(extensionOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_EXTENSION,
					   stmt->extname);


	control = read_extension_control_file(stmt->extname);


	foreach(lc, stmt->options)
	{
		DefElem    *defel = (DefElem *) lfirst(lc);

		if (strcmp(defel->defname, "new_version") == 0)
		{
			if (d_new_version)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("conflicting or redundant options")));
			d_new_version = defel;
		}
		else
			elog(ERROR, "unrecognized option: %s", defel->defname);
	}


	if (d_new_version && d_new_version->arg)
		versionName = strVal(d_new_version->arg);
	else if (control->default_version)
		versionName = control->default_version;
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("version to install must be specified")));
		versionName = NULL;
	}
	check_valid_version_name(versionName);


	if (strcmp(oldVersionName, versionName) == 0)
	{
		ereport(NOTICE,
		   (errmsg("version \"%s\" of extension \"%s\" is already installed",
				   versionName, stmt->extname)));
		return;
	}


	updateVersions = identify_update_path(control,
										  oldVersionName,
										  versionName);


	ApplyExtensionUpdates(extensionOid, control,
						  oldVersionName, updateVersions);
}
