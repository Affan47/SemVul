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
				heap_insert_slot(node, i);
		}
		node->ms_initialized = true;
	}
	else
	{


		i = node->ms_last_slot;
		node->ms_slots[i] = ExecProcNode(node->mergeplans[i]);
		if (!TupIsNull(node->ms_slots[i]))
			heap_insert_slot(node, i);
	}

	if (node->ms_heap_size > 0)
	{

		i = node->ms_heap[0];
		result = node->ms_slots[i];
		node->ms_last_slot = i;
		heap_siftup_slot(node);
	}
	else
	{

		result = ExecClearTuple(node->ps.ps_ResultTupleSlot);
	}

	return result;
}
