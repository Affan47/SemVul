computePartialMatchList(GinBtreeData *btree, GinBtreeStack *stack, GinScanEntry scanEntry)
{
	Page		page;
	IndexTuple	itup;
	Datum		idatum;
	int32		cmp;

	scanEntry->partialMatch = tbm_create(work_mem * 1024L);

	for (;;)
	{


		if (moveRightIfItNeeded(btree, stack) == false)
			return true;

		page = BufferGetPage(stack->buffer);
		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));


		if (gintuple_get_attrnum(btree->ginstate, itup) != scanEntry->attnum)
			return true;

		idatum = gin_index_getattr(btree->ginstate, itup);


		cmp = DatumGetInt32(FunctionCall4(&btree->ginstate->comparePartialFn[scanEntry->attnum - 1],
										  scanEntry->entry,
										  idatum,
										  UInt16GetDatum(scanEntry->strategy),
									PointerGetDatum(scanEntry->extra_data)));

		if (cmp > 0)
			return true;
		else if (cmp < 0)
		{
			stack->off++;
			continue;
		}

		if (GinIsPostingTree(itup))
		{
			BlockNumber rootPostingTree = GinGetPostingTree(itup);
			Datum		newDatum,
						savedDatum = datumCopy(
											   idatum,
											   btree->ginstate->origTupdesc->attrs[scanEntry->attnum - 1]->attbyval,
			btree->ginstate->origTupdesc->attrs[scanEntry->attnum - 1]->attlen
			);


			LockBuffer(stack->buffer, GIN_UNLOCK);
			scanForItems(btree->index, scanEntry, rootPostingTree);


			LockBuffer(stack->buffer, GIN_SHARE);
			page = BufferGetPage(stack->buffer);
			if (!GinPageIsLeaf(page))
			{


				return false;
			}

			for (;;)
			{
				if (moveRightIfItNeeded(btree, stack) == false)
					elog(ERROR, "lost saved point in index");

				page = BufferGetPage(stack->buffer);
				itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));
				newDatum = gin_index_getattr(btree->ginstate, itup);

				if (gintuple_get_attrnum(btree->ginstate, itup) != scanEntry->attnum)
					elog(ERROR, "lost saved point in index");

				if (compareEntries(btree->ginstate, scanEntry->attnum, newDatum, savedDatum) == 0)
				{

					if (btree->ginstate->origTupdesc->attrs[scanEntry->attnum - 1]->attbyval == false)
						pfree(DatumGetPointer(savedDatum));
					break;
				}

				stack->off++;
			}
		}
		else
		{
			tbm_add_tuples(scanEntry->partialMatch, GinGetPosting(itup), GinGetNPosting(itup), false);
			scanEntry->predictNumberResult += GinGetNPosting(itup);
		}


		stack->off++;
	}

	return true;
}
