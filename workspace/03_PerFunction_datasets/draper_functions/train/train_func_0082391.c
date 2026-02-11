build_datatype(HeapTuple typeTup, int32 typmod)
{
	Form_pg_type typeStruct = (Form_pg_type) GETSTRUCT(typeTup);
	PLpgSQL_type *typ;

	if (!typeStruct->typisdefined)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type \"%s\" is only a shell",
						NameStr(typeStruct->typname))));

	typ = (PLpgSQL_type *) palloc(sizeof(PLpgSQL_type));

	typ->typname = pstrdup(NameStr(typeStruct->typname));
	typ->typoid = HeapTupleGetOid(typeTup);
	switch (typeStruct->typtype)
	{
		case 'b':
		case 'd':
			typ->ttype = PLPGSQL_TTYPE_SCALAR;
			break;
		case 'c':
			Assert(OidIsValid(typeStruct->typrelid));
			typ->ttype = PLPGSQL_TTYPE_ROW;
			break;
		case 'p':
			if (typ->typoid == RECORDOID)
				typ->ttype = PLPGSQL_TTYPE_REC;
			else
				typ->ttype = PLPGSQL_TTYPE_PSEUDO;
			break;
		default:
			elog(ERROR, "unrecognized typtype: %d",
				 (int) typeStruct->typtype);
			break;
	}
	typ->typlen = typeStruct->typlen;
	typ->typbyval = typeStruct->typbyval;
	typ->typrelid = typeStruct->typrelid;
	typ->typioparam = getTypeIOParam(typeTup);
	fmgr_info(typeStruct->typinput, &(typ->typinput));
	typ->atttypmod = typmod;

	return typ;
}
