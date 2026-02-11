compute_balloon_floor(void)
{
	unsigned long min_pages;
#define MB2PAGES(mb) ((mb) << (20 - PAGE_SHIFT))


	if (totalram_pages < MB2PAGES(128))
		min_pages = MB2PAGES(8) + (totalram_pages >> 1);
	else if (totalram_pages < MB2PAGES(512))
		min_pages = MB2PAGES(40) + (totalram_pages >> 2);
	else if (totalram_pages < MB2PAGES(2048))
		min_pages = MB2PAGES(104) + (totalram_pages >> 3);
	else if (totalram_pages < MB2PAGES(8192))
		min_pages = MB2PAGES(232) + (totalram_pages >> 4);
	else
		min_pages = MB2PAGES(488) + (totalram_pages >> 5);
#undef MB2PAGES
	return min_pages;
}
