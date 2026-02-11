sfi_find_syst(void)
{
	unsigned long offset, len;
	void *start;

	len = SFI_SYST_SEARCH_END - SFI_SYST_SEARCH_BEGIN;
	start = sfi_map_memory(SFI_SYST_SEARCH_BEGIN, len);
	if (!start)
		return -1;

	for (offset = 0; offset < len; offset += 16) {
		struct sfi_table_header *syst_hdr;

		syst_hdr = start + offset;
		if (strncmp(syst_hdr->sig, SFI_SIG_SYST,
				SFI_SIGNATURE_SIZE))
			continue;

		if (syst_hdr->len > PAGE_SIZE)
			continue;

		sfi_print_table_header(SFI_SYST_SEARCH_BEGIN + offset,
					syst_hdr);

		if (sfi_verify_table(syst_hdr))
			continue;


		if (!ON_SAME_PAGE(syst_pa, syst_pa + syst_hdr->len)) {
			pr_info("SYST 0x%llx + 0x%x crosses page\n",
					syst_pa, syst_hdr->len);
			continue;
		}


		syst_pa = SFI_SYST_SEARCH_BEGIN + offset;
		sfi_unmap_memory(start, len);
		return 0;
	}

	sfi_unmap_memory(start, len);
	return -1;
}
