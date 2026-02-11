TupleHashTableMatch(const void *key1, const void *key2, Size keysize)
{
	MinimalTuple tuple1 = ((const TupleHashEntryData *) key1)->firstTuple;

#ifdef USE_ASSERT_CHECKING
	MinimalTuple tuple2 = ((const TupleHashEntryData *) key2)->firstTuple;
#endif
	TupleTableSlot *slot1;
	TupleTableSlot *slot2;
	TupleHashTable hashtable = CurTupleHashTable;


	Assert(tuple1 != NULL);
	slot1 = hashtable->tableslot;
	ExecStoreMinimalTuple(tuple1, slot1, false);
	Assert(tuple2 == NULL);
	slot2 = hashtable->inputslot;


	if (execTuplesMatch(slot2,
						slot1,
						hashtable->numCols,
						hashtable->keyColIdx,
						hashtable->cur_eq_funcs,
						hashtable->tempcxt))
		return 0;
	else
		return 1;
}
