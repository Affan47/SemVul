init_csrows(struct mem_ctl_info *mci)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	struct csrow_info *csrow;
	struct dimm_info *dimm;
	enum edac_type edac_mode;
	int i, j, empty = 1;
	int nr_pages = 0;
	u32 val;

	amd64_read_pci_cfg(pvt->F3, NBCFG, &val);

	pvt->nbcfg = val;

	edac_dbg(0, "node %d, NBCFG=0x%08x[ChipKillEccCap: %d|DramEccEn: %d]\n",
		 pvt->mc_node_id, val,
		 !!(val & NBCFG_CHIPKILL), !!(val & NBCFG_ECC_ENABLE));


	for_each_chip_select(i, 0, pvt) {
		bool row_dct0 = !!csrow_enabled(i, 0, pvt);
		bool row_dct1 = false;

		if (pvt->fam != 0xf)
			row_dct1 = !!csrow_enabled(i, 1, pvt);

		if (!row_dct0 && !row_dct1)
			continue;

		csrow = mci->csrows[i];
		empty = 0;

		edac_dbg(1, "MC node: %d, csrow: %d\n",
			    pvt->mc_node_id, i);

		if (row_dct0) {
			nr_pages = get_csrow_nr_pages(pvt, 0, i);
			csrow->channels[0]->dimm->nr_pages = nr_pages;
		}


		if (pvt->fam != 0xf && row_dct1) {
			int row_dct1_pages = get_csrow_nr_pages(pvt, 1, i);

			csrow->channels[1]->dimm->nr_pages = row_dct1_pages;
			nr_pages += row_dct1_pages;
		}

		edac_dbg(1, "Total csrow%d pages: %u\n", i, nr_pages);


		if (pvt->nbcfg & NBCFG_ECC_ENABLE)
			edac_mode = (pvt->nbcfg & NBCFG_CHIPKILL) ?
				    EDAC_S4ECD4ED : EDAC_SECDED;
		else
			edac_mode = EDAC_NONE;

		for (j = 0; j < pvt->channel_count; j++) {
			dimm = csrow->channels[j]->dimm;
			dimm->mtype = pvt->dram_type;
			dimm->edac_mode = edac_mode;
		}
	}

	return empty;
}
