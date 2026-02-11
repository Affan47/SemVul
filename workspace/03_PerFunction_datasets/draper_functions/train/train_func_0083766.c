i5100_init_csrows(struct mem_ctl_info *mci)
{
	int i;
	struct i5100_priv *priv = mci->pvt_info;

	for (i = 0; i < mci->tot_dimms; i++) {
		struct dimm_info *dimm;
		const unsigned long npages = i5100_npages(mci, i);
		const unsigned chan = i5100_csrow_to_chan(mci, i);
		const unsigned rank = i5100_csrow_to_rank(mci, i);

		if (!npages)
			continue;

		dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms, mci->n_layers,
			       chan, rank, 0);

		dimm->nr_pages = npages;
		dimm->grain = 32;
		dimm->dtype = (priv->mtr[chan][rank].width == 4) ?
				DEV_X4 : DEV_X8;
		dimm->mtype = MEM_RDDR2;
		dimm->edac_mode = EDAC_SECDED;
		snprintf(dimm->label, sizeof(dimm->label), "DIMM%u",
			 i5100_rank_to_slot(mci, chan, rank));

		edac_dbg(2, "dimm channel %d, rank %d, size %ld\n",
			 chan, rank, (long)PAGES_TO_MiB(npages));
	}
}
