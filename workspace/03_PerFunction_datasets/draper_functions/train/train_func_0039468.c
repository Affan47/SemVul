IsSystemClass(Oid relid, Form_pg_class reltuple)
{
	return IsToastClass(reltuple) || IsCatalogClass(relid, reltuple);
}
