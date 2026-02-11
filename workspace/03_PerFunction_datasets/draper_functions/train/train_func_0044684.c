PageAddItem(Page page,
			Item item,
			Size size,
			OffsetNumber offsetNumber,
			ItemIdFlags flags)
{
	PageHeader	phdr = (PageHeader) page;
	Size		alignedSize;
	int			lower;
	int			upper;
	ItemId		itemId;
	OffsetNumber limit;
	bool		needshuffle = false;
	bool		overwritemode = (flags & OverwritePageMode) != 0;

	flags &= ~OverwritePageMode;


	if (phdr->pd_lower < SizeOfPageHeaderData ||
		phdr->pd_lower > phdr->pd_upper ||
		phdr->pd_upper > phdr->pd_special ||
		phdr->pd_special > BLCKSZ)
		ereport(PANIC,
				(errcode(ERRCODE_DATA_CORRUPTED),
				 errmsg("corrupted page pointers: lower = %u, upper = %u, special = %u",
						phdr->pd_lower, phdr->pd_upper, phdr->pd_special)));


	limit = OffsetNumberNext(PageGetMaxOffsetNumber(page));


	if (OffsetNumberIsValid(offsetNumber))
	{

		if (overwritemode)
		{
			if (offsetNumber < limit)
			{
				itemId = PageGetItemId(phdr, offsetNumber);
				if (ItemIdIsUsed(itemId) || ItemIdGetLength(itemId) != 0)
				{
					elog(WARNING, "will not overwrite a used ItemId");
					return InvalidOffsetNumber;
				}
			}
		}
		else
		{
			if (offsetNumber < limit)
				needshuffle = true;
		}
	}
	else
	{


		for (offsetNumber = 1; offsetNumber < limit; offsetNumber++)
		{
			itemId = PageGetItemId(phdr, offsetNumber);
			if (!ItemIdIsUsed(itemId) && ItemIdGetLength(itemId) == 0)
				break;
		}

	}

	if (offsetNumber > limit)
	{
		elog(WARNING, "specified item offset is too large");
		return InvalidOffsetNumber;
	}


	if (offsetNumber == limit || needshuffle)
		lower = phdr->pd_lower + sizeof(ItemIdData);
	else
		lower = phdr->pd_lower;

	alignedSize = MAXALIGN(size);

	upper = (int) phdr->pd_upper - (int) alignedSize;

	if (lower > upper)
		return InvalidOffsetNumber;


	itemId = PageGetItemId(phdr, offsetNumber);

	if (needshuffle)
		memmove(itemId + 1, itemId,
				(limit - offsetNumber) * sizeof(ItemIdData));


	itemId->lp_off = upper;
	itemId->lp_len = size;
	itemId->lp_flags = flags;


	memcpy((char *) page + upper, item, size);


	phdr->pd_lower = (LocationIndex) lower;
	phdr->pd_upper = (LocationIndex) upper;

	return offsetNumber;
}
