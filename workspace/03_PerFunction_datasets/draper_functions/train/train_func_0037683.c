lookup_fsm_page_entry(FSMRelation *fsmrel, BlockNumber page,
					  int *outPageIndex)
{

	if (fsmrel->storedPages <= 0)
	{
		*outPageIndex = 0;
		return false;
	}


	if (fsmrel->isIndex)
	{
		IndexFSMPageData *info;
		int			low,
					high;

		info = (IndexFSMPageData *)
			(FreeSpaceMap->arena + fsmrel->firstChunk * CHUNKBYTES);
		low = 0;
		high = fsmrel->storedPages - 1;
		while (low <= high)
		{
			int			middle;
			BlockNumber probe;

			middle = low + (high - low) / 2;
			probe = IndexFSMPageGetPageNum(info + middle);
			if (probe == page)
			{
				*outPageIndex = middle;
				return true;
			}
			else if (probe < page)
				low = middle + 1;
			else
				high = middle - 1;
		}
		*outPageIndex = low;
		return false;
	}
	else
	{
		FSMPageData *info;
		int			low,
					high;

		info = (FSMPageData *)
			(FreeSpaceMap->arena + fsmrel->firstChunk * CHUNKBYTES);
		low = 0;
		high = fsmrel->storedPages - 1;
		while (low <= high)
		{
			int			middle;
			BlockNumber probe;

			middle = low + (high - low) / 2;
			probe = FSMPageGetPageNum(info + middle);
			if (probe == page)
			{
				*outPageIndex = middle;
				return true;
			}
			else if (probe < page)
				low = middle + 1;
			else
				high = middle - 1;
		}
		*outPageIndex = low;
		return false;
	}
}
