hpsa_put_ctlr_into_performant_mode(struct ctlr_info *h)
{
	u32 trans_support;
	unsigned long transMethod = CFGTBL_Trans_Performant |
					CFGTBL_Trans_use_short_tags;
	int i, rc;

	if (hpsa_simple_mode)
		return 0;

	trans_support = readl(&(h->cfgtable->TransportSupport));
	if (!(trans_support & PERFORMANT_MODE))
		return 0;


	if (trans_support & CFGTBL_Trans_io_accel1) {
		transMethod |= CFGTBL_Trans_io_accel1 |
				CFGTBL_Trans_enable_directed_msix;
		rc = hpsa_alloc_ioaccel1_cmd_and_bft(h);
		if (rc)
			return rc;
	} else if (trans_support & CFGTBL_Trans_io_accel2) {
		transMethod |= CFGTBL_Trans_io_accel2 |
				CFGTBL_Trans_enable_directed_msix;
		rc = hpsa_alloc_ioaccel2_cmd_and_bft(h);
		if (rc)
			return rc;
	}

	h->nreply_queues = h->msix_vector > 0 ? h->msix_vector : 1;
	hpsa_get_max_perf_mode_cmds(h);

	h->reply_queue_size = h->max_commands * sizeof(u64);

	for (i = 0; i < h->nreply_queues; i++) {
		h->reply_queue[i].head = pci_alloc_consistent(h->pdev,
						h->reply_queue_size,
						&(h->reply_queue[i].busaddr));
		if (!h->reply_queue[i].head) {
			rc = -ENOMEM;
			goto clean1;
		}
		h->reply_queue[i].size = h->max_commands;
		h->reply_queue[i].wraparound = 1;
		h->reply_queue[i].current_entry = 0;
	}


	h->blockFetchTable = kmalloc(((SG_ENTRIES_IN_CMD + 1) *
				sizeof(u32)), GFP_KERNEL);
	if (!h->blockFetchTable) {
		rc = -ENOMEM;
		goto clean1;
	}

	rc = hpsa_enter_performant_mode(h, trans_support);
	if (rc)
		goto clean2;
	return 0;

clean2:
	kfree(h->blockFetchTable);
	h->blockFetchTable = NULL;
clean1:
	hpsa_free_reply_queues(h);
	hpsa_free_ioaccel1_cmd_and_bft(h);
	hpsa_free_ioaccel2_cmd_and_bft(h);
	return rc;
}
