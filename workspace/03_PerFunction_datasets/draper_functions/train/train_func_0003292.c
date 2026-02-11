netdump_page_size(void)
{
	if (!VMCORE_VALID())
		return 0;

	return nd->page_size;
}
