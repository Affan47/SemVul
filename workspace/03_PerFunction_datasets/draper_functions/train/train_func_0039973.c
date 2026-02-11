countPage(PageType pt)
{
    pageNumber++;
    pageNumberOfJob++;

    if (pt == PAGE_COVER)
	 pageNumberCovered++;
    if (pt == PAGE_SKIP)
	pageNumberSkipped++;
}
