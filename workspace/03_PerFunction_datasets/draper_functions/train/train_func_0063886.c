forgetIncompleteInsert(RelFileNode node, ItemPointerData key)
{
	ListCell   *l;

	if (!ItemPointerIsValid(&key))
		return;

	if (incomplete_inserts == NIL)
		return;

	foreach(l, incomplete_inserts)
	{
		gistIncompleteInsert *insert = (gistIncompleteInsert *) lfirst(l);

		if (RelFileNodeEquals(node, insert->node) && ItemPointerEQ(&(insert->key), &(key)))
		{

			incomplete_inserts = list_delete_ptr(incomplete_inserts, insert);
			pfree(insert->blkno);
			pfree(insert);
			break;
		}
	}
}
