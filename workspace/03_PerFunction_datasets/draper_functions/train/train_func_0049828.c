roles_has_privs_of(Oid roleid)
{
	List	   *roles_list;
	ListCell   *l;
	List	   *new_cached_privs_roles;
	MemoryContext oldctx;


	if (OidIsValid(cached_privs_role) && cached_privs_role == roleid)
		return cached_privs_roles;


	roles_list = list_make1_oid(roleid);

	foreach(l, roles_list)
	{
		Oid			memberid = lfirst_oid(l);
		CatCList   *memlist;
		int			i;


		if (!has_rolinherit(memberid))
			continue;


		memlist = SearchSysCacheList(AUTHMEMMEMROLE, 1,
									 ObjectIdGetDatum(memberid),
									 0, 0, 0);
		for (i = 0; i < memlist->n_members; i++)
		{
			HeapTuple	tup = &memlist->members[i]->tuple;
			Oid			otherid = ((Form_pg_auth_members) GETSTRUCT(tup))->roleid;


			roles_list = list_append_unique_oid(roles_list, otherid);
		}
		ReleaseSysCacheList(memlist);
	}


	oldctx = MemoryContextSwitchTo(TopMemoryContext);
	new_cached_privs_roles = list_copy(roles_list);
	MemoryContextSwitchTo(oldctx);
	list_free(roles_list);


	cached_privs_role = InvalidOid;
	list_free(cached_privs_roles);
	cached_privs_roles = new_cached_privs_roles;
	cached_privs_role = roleid;


	return cached_privs_roles;
}
