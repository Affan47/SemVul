ExecMergeAppend(MergeAppendState *node)
{
	TupleTableSlot *result;
	SlotNumber	i;

	if (!node->ms_initialized)
	{


		for (i = 0; i < node->ms_nplans; i++)
		{
			node->ms_slots[i] = ExecProcNode(node->mergeplans[i]);
			if (!TupIsNull(node->ms_slots[i]))
				binaryheap_add_unordered(node->ms_heap, Int32GetDatum(i));
		}
		binaryheap_build(node->ms_heap);
		node->ms_initialized = true;
	}
	else
	{


		i = DatumGetInt32(binaryheap_first(node->ms_heap));
		node->ms_slots[i] = ExecProcNode(node->mergeplans[i]);
		if (!TupIsNull(node->ms_slots[i]))
			binaryheap_replace_first(node->ms_heap, Int32GetDatum(i));
		else
			(void) binaryheap_remove_first(node->ms_heap);
	}

	if (binaryheap_empty(node->ms_heap))
	{

		result = ExecClearTuple(node->ps.ps_ResultTupleSlot);
	}
	else
	{
		i = DatumGetInt32(binaryheap_first(node->ms_heap));
		result = node->ms_slots[i];
	}

	return result;
}
