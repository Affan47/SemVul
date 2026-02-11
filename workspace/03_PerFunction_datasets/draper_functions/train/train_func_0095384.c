ddp_clear_map(struct cxgbi_hba *chba, unsigned int tag,
			  unsigned int idx, unsigned int npods)
{
	struct cxgbi_device *cdev = chba->cdev;
	struct cxgbi_ddp_info *ddp = cdev->ddp;
	unsigned int pm_addr = (idx << PPOD_SIZE_SHIFT) + ddp->llimit;
	int i;

	log_debug(1 << CXGBI_DBG_DDP,
		"cdev 0x%p, idx %u, npods %u, tag 0x%x.\n",
		cdev, idx, npods, tag);

	for (i = 0; i < npods; i++, idx++, pm_addr += PPOD_SIZE) {
		struct sk_buff *skb = alloc_wr(sizeof(struct ulp_mem_io) +
						PPOD_SIZE, 0, GFP_ATOMIC);

		if (!skb) {
			pr_err("tag 0x%x, 0x%x, %d/%u, skb OOM.\n",
				tag, idx, i, npods);
			continue;
		}
		ulp_mem_io_set_hdr(skb, pm_addr);
		skb->priority = CPL_PRIORITY_CONTROL;
		cxgb3_ofld_send(cdev->lldev, skb);
	}
}
