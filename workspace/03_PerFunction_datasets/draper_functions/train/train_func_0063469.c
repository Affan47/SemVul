list_difference_oid(List *list1, List *list2)
{
	ListCell   *cell;
	List	   *result = NIL;

	Assert(IsOidList(list1));
	Assert(IsOidList(list2));

	if (list2 == NIL)
		return list_copy(list1);

	foreach(cell, list1)
	{
		if (!list_member_oid(list2, lfirst_oid(cell)))
			result = lappend_oid(result, lfirst_oid(cell));
	}

	check_list_invariants(result);
	return result;
}
