fixup_any_bank_any_page(int start_page, int num_pages, byte *mem0rd,
		byte *mem0wr)
{
	int	i;

	for(i = 0; i < num_pages; i++) {
		SET_PAGE_INFO_RD(i + start_page, mem0rd);
		mem0rd += 0x100;
	}

	for(i = 0; i < num_pages; i++) {
		SET_PAGE_INFO_WR(i + start_page, mem0wr);
		mem0wr += 0x100;
	}

}
