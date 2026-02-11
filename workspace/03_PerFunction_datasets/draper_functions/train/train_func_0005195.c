pack_incoming_pages(FSMPageData *newLocation, int newPages,
					PageFreeSpaceInfo *pageSpaces, int nPages)
{
	int			histogram[HISTOGRAM_BINS];
	int			above,
				binct,
				i;
	Size		thresholdL,
				thresholdU;

	Assert(newPages < nPages);

	MemSet(histogram, 0, sizeof(histogram));
	for (i = 0; i < nPages; i++)
	{
		Size		avail = pageSpaces[i].avail;

		if (avail >= BLCKSZ)
			elog(ERROR, "bogus freespace amount");
		avail /= (BLCKSZ / HISTOGRAM_BINS);
		histogram[avail]++;
	}

	above = 0;
	for (i = HISTOGRAM_BINS - 1; i >= 0; i--)
	{
		int			sum = above + histogram[i];

		if (sum > newPages)
			break;
		above = sum;
	}
	Assert(i >= 0);
	thresholdL = i * BLCKSZ / HISTOGRAM_BINS;
	thresholdU = (i + 1) * BLCKSZ / HISTOGRAM_BINS;
	binct = newPages - above;

	for (i = 0; i < nPages; i++)
	{
		BlockNumber page = pageSpaces[i].blkno;
		Size		avail = pageSpaces[i].avail;


		if (i > 0 && page <= pageSpaces[i - 1].blkno)
			elog(ERROR, "free-space data is not in page order");

		if (avail >= thresholdU ||
			(avail >= thresholdL && (--binct >= 0)))
		{
			FSMPageSetPageNum(newLocation, page);
			FSMPageSetSpace(newLocation, avail);
			newLocation++;
			newPages--;
		}
	}
	Assert(newPages == 0);
}
