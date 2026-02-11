hpsa_free_ioaccel1_cmd_and_bft(struct ctlr_info *h)
{
	if (h->ioaccel_cmd_pool) {
		pci_free_consistent(h->pdev,
			h->nr_cmds * sizeof(*h->ioaccel_cmd_pool),
			h->ioaccel_cmd_pool,
			h->ioaccel_cmd_pool_dhandle);
		h->ioaccel_cmd_pool = NULL;
		h->ioaccel_cmd_pool_dhandle = 0;
	}
	kfree(h->ioaccel1_blockFetchTable);
	h->ioaccel1_blockFetchTable = NULL;
}
