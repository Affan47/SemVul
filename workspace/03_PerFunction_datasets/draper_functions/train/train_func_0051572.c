PageHeaderIsValid(PageHeader page)
{
	char	   *pagebytes;
	int			i;


	if (PageGetPageSize(page) == BLCKSZ &&
		PageGetPageLayoutVersion(page) == PG_PAGE_LAYOUT_VERSION &&
		(page->pd_flags & ~PD_VALID_FLAG_BITS) == 0 &&
		page->pd_lower >= SizeOfPageHeaderData &&
		page->pd_lower <= page->pd_upper &&
		page->pd_upper <= page->pd_special &&
		page->pd_special <= BLCKSZ &&
		page->pd_special == MAXALIGN(page->pd_special))
		return true;


	pagebytes = (char *) page;
	for (i = 0; i < BLCKSZ; i++)
	{
		if (pagebytes[i] != 0)
			return false;
	}
	return true;
}
