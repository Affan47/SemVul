dump_sdvo_panel_dtds(int length)
{
	struct bdb_block *block;
	struct lvds_dvo_timing2 *dvo_timing;
	int n, count;

	block = find_section(BDB_SDVO_PANEL_DTDS, length);
	if (!block) {
		printf("No SDVO panel dtds block\n");
		return;
	}

	printf("SDVO panel dtds:\n");
	count = block->size / sizeof(struct lvds_dvo_timing2);
	dvo_timing = block->data;
	for (n = 0; n < count; n++) {
		printf("%d:\n", n);
		print_detail_timing_data(dvo_timing++);
	}

	free(block);
}
