roleSpecsToIds(List *memberNames)
{
	List	   *result = NIL;
	ListCell   *l;

	foreach(l, memberNames)
	{
		Node	   *rolespec = (Node *) lfirst(l);
		Oid			roleid;

		roleid = get_rolespec_oid(rolespec, false);
		result = lappend_oid(result, roleid);
	}
	return result;
}
