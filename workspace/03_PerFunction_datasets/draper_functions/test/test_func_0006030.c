agg_fill_hash_table(AggState *aggstate)
{
	ExprContext *tmpcontext;
	AggHashEntry entry;
	TupleTableSlot *outerslot;


	tmpcontext = aggstate->tmpcontext;


	for (;;)
	{
		outerslot = fetch_input_tuple(aggstate);
		if (TupIsNull(outerslot))
			break;

		tmpcontext->ecxt_outertuple = outerslot;


		entry = lookup_hash_entry(aggstate, outerslot);


		advance_aggregates(aggstate, entry->pergroup);


		ResetExprContext(tmpcontext);
	}

	aggstate->table_filled = true;

	ResetTupleHashIterator(aggstate->hashtable, &aggstate->hashiter);
}
