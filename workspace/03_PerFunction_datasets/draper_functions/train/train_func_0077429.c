list_member_int(List *list, int datum)
{
	ListCell   *cell;

	Assert(IsIntegerList(list));
	check_list_invariants(list);

	foreach(cell, list)
	{
		if (lfirst_int(cell) == datum)
			return true;
	}

	return false;
}
