diag_show_pda(const char *dev)
{
	char fname[256];
	struct prism2_pda pda;
	int i, j;

	printf("\nProduction Data Area (PDA)\n\n");

	snprintf(fname, sizeof(fname), "/proc/net/hostap/%s/pda", dev);
	if (read_wlan_pda(fname, &pda)) {
		printf("Could not read wlan PDA. This requires "
		       "PRISM2_DOWNLOAD_SUPPORT definition for the kernel "
		       "driver.\n");
		return;
	}

	for (i = 0; i < pda.pdr_count; i++) {
		printf("PDR 0x%04x len=%i %s\n  ",
		       pda.pdrs[i].pdr, pda.pdrs[i].len,
		       prism2_pdr_name(pda.pdrs[i].pdr));
		for (j = 0; j < pda.pdrs[i].len; j++)
			printf(" %02x", pda.pdrs[i].data[j]);
		printf("\n");
	}

	free(pda.pdrs);
}
