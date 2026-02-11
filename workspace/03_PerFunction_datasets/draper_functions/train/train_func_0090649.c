GinDataLeafPageGetItems(Page page, int *nitems, ItemPointerData advancePast)
{
	ItemPointer result;

	if (GinPageIsCompressed(page))
	{
		GinPostingList *seg = GinDataLeafPageGetPostingList(page);
		Size		len = GinDataLeafPageGetPostingListSize(page);
		Pointer		endptr = ((Pointer) seg) + len;
		GinPostingList *next;


		if (ItemPointerIsValid(&advancePast))
		{
			next = GinNextPostingListSegment(seg);
			while ((Pointer) next < endptr &&
				   ginCompareItemPointers(&next->first, &advancePast) <= 0)
			{
				seg = next;
				next = GinNextPostingListSegment(seg);
			}
			len = endptr - (Pointer) seg;
		}

		if (len > 0)
			result = ginPostingListDecodeAllSegments(seg, len, nitems);
		else
		{
			result = NULL;
			*nitems = 0;
		}
	}
	else
	{
		ItemPointer tmp = dataLeafPageGetUncompressed(page, nitems);

		result = palloc((*nitems) * sizeof(ItemPointerData));
		memcpy(result, tmp, (*nitems) * sizeof(ItemPointerData));
	}

	return result;
}
