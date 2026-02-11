selectDumpableType(TypeInfo *tyinfo)
{

	if (OidIsValid(tyinfo->typrelid) &&
		tyinfo->typrelkind != RELKIND_COMPOSITE_TYPE)
	{
		tyinfo->dobj.dump = false;
		tyinfo->dobj.objType = DO_DUMMY_TYPE;
	}


	else if (tyinfo->isArray)
	{
		tyinfo->dobj.dump = false;
		tyinfo->dobj.objType = DO_DUMMY_TYPE;
	}


	else if (!tyinfo->dobj.namespace->dobj.dump)
		tyinfo->dobj.dump = false;


	else if (!tyinfo->isDefined)
		tyinfo->dobj.dump = false;

	else
		tyinfo->dobj.dump = true;
}
