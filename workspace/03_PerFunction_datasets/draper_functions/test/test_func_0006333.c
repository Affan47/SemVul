FuncNameAsType(List *funcname)
{
	Oid			result;
	Type		typtup;

	typtup = LookupTypeName(NULL, makeTypeNameFromNameList(funcname), NULL, false);
	if (typtup == NULL)
		return InvalidOid;

	if (((Form_pg_type) GETSTRUCT(typtup))->typisdefined &&
		!OidIsValid(typeTypeRelid(typtup)))
		result = typeTypeId(typtup);
	else
		result = InvalidOid;

	ReleaseSysCache(typtup);
	return result;
}
