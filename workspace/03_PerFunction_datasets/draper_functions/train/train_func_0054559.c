find_free_space(FSMRelation *fsmrel, Size spaceNeeded)
{
	FSMPageData *info;
	int			pagesToCheck,
				pageIndex;

	if (fsmrel->isIndex)
		elog(ERROR, "find_free_space called for an index relation");
	info = (FSMPageData *)
		(FreeSpaceMap->arena + fsmrel->firstChunk * CHUNKBYTES);
	pageIndex = fsmrel->nextPage;

	if (pageIndex >= fsmrel->storedPages)
		pageIndex = 0;

	for (pagesToCheck = fsmrel->storedPages; pagesToCheck > 0; pagesToCheck--)
	{
		FSMPageData *page = info + pageIndex;
		Size		spaceAvail = FSMPageGetSpace(page);


		if (spaceAvail >= spaceNeeded)
		{


			FSMPageSetSpace(page, spaceAvail - spaceNeeded);
			fsmrel->nextPage = pageIndex + 1;
			return FSMPageGetPageNum(page);
		}

		if (++pageIndex >= fsmrel->storedPages)
			pageIndex = 0;
	}

	return InvalidBlockNumber;
}
