hptiop_internal_memalloc_mvfrey(struct hptiop_hba *hba)
{
	u32 list_count = readl(&hba->u.mvfrey.mu->inbound_conf_ctl);
	char *p;
	dma_addr_t phy;

	BUG_ON(hba->max_request_size == 0);

	if (list_count == 0) {
		BUG_ON(1);
		return -1;
	}

	list_count >>= 16;

	hba->u.mvfrey.list_count = list_count;
	hba->u.mvfrey.internal_mem_size = 0x800 +
			list_count * sizeof(struct mvfrey_inlist_entry) +
			list_count * sizeof(struct mvfrey_outlist_entry) +
			sizeof(int);

	p = dma_alloc_coherent(&hba->pcidev->dev,
			hba->u.mvfrey.internal_mem_size, &phy, GFP_KERNEL);
	if (!p)
		return -1;

	hba->u.mvfrey.internal_req.req_virt = p;
	hba->u.mvfrey.internal_req.req_shifted_phy = phy >> 5;
	hba->u.mvfrey.internal_req.scp = NULL;
	hba->u.mvfrey.internal_req.next = NULL;

	p += 0x800;
	phy += 0x800;

	hba->u.mvfrey.inlist = (struct mvfrey_inlist_entry *)p;
	hba->u.mvfrey.inlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_inlist_entry);
	phy += list_count * sizeof(struct mvfrey_inlist_entry);

	hba->u.mvfrey.outlist = (struct mvfrey_outlist_entry *)p;
	hba->u.mvfrey.outlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_outlist_entry);
	phy += list_count * sizeof(struct mvfrey_outlist_entry);

	hba->u.mvfrey.outlist_cptr = (__le32 *)p;
	hba->u.mvfrey.outlist_cptr_phy = phy;

	return 0;
}
