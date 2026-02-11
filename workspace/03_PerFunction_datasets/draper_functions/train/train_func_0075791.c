get_server_option(Objid oid, const char *name, Var * r)
{
    if (((valid(oid) &&
	  db_find_property(oid, "server_options", r).ptr)
	 || (valid(SYSTEM_OBJECT) &&
	     db_find_property(SYSTEM_OBJECT, "server_options", r).ptr))
	&& r->type == TYPE_OBJ
	&& valid(r->v.obj)
	&& db_find_property(r->v.obj, name, r).ptr)
	return 1;

    return 0;
}
